#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <string>
#include <vector>

#include "external_sort.h"

namespace {
	struct positional_value {
    	uint64_t val, pos, max;

    	bool operator>(const positional_value& other) const {
    		return val > other.val;
    	}
	};
}

void external_sort(const std::string& input_path,
                   const std::string& output_path, size_t num_threads) {
    static const std::string tmp_path = "tmp.bin";
	constexpr size_t buf_size = 3145728;

	std::ifstream input{input_path, std::ios::binary};
    std::ofstream output{output_path, std::ios::binary},
                  tmp{tmp_path, std::ios::binary};

	if (!input) throw std::runtime_error{"Error opening input file"};
	if (!output) throw std::runtime_error{"Error opening output file"};
	if (!tmp) throw std::runtime_error{"Error opening tmp file"};

    std::mutex read_mutex, write_mutex;

	auto sort = [buf_size](std::mutex& read_mutex, std::mutex& write_mutex,
		                      std::ifstream& input, std::ofstream& tmp) {
		std::unique_ptr<uint64_t[]> arr{
            new uint64_t[buf_size / sizeof(uint64_t)]};
		for (;;) {
            {
    			std::unique_lock<std::mutex> lock{read_mutex};
                input.read((char*)arr.get(), buf_size);
            } // lock read
            auto read_count = input.gcount();

			if (read_count == 0) break;
			std::sort(arr.get(), arr.get() + read_count / sizeof(uint64_t));

            {
				std::unique_lock<std::mutex> lock(write_mutex);
				tmp.write((char*)&read_count, sizeof(size_t));
				tmp.write((char*)arr.get(), read_count);
            } // lock write
		}
	};

	auto sort_function = std::bind(sort, std::ref(read_mutex),
                                   std::ref(write_mutex), std::ref(input),
                                   std::ref(tmp));

	std::vector<std::thread> workers;
	for (int i = 0; i < num_threads; ++i) {
	 	workers.emplace_back(sort_function);
	}

	for (int i = 0; i < num_threads; ++i) {
		workers[i].join();
    }

	tmp.close();
	input.close();

	input.open(tmp_path, std::ios::binary);
	if (!input) throw std::runtime_error{"Error openning tmp file\n"};

	std::priority_queue<positional_value, std::vector<positional_value>,
                        std::greater<positional_value>> queue;
	for (;;) {
		uint64_t buf;
		size_t count;

		if (!input.read((char*)&count, sizeof(size_t))) break;

		input.read((char*)&buf, sizeof(uint64_t));
		queue.push({buf, static_cast<uint64_t>(input.tellg()),
            static_cast<uint64_t>(input.tellg()) + count -
            sizeof(uint64_t)});
		input.seekg(count - sizeof(uint64_t), std::ios::cur);
	}
	input.clear();

	while (!queue.empty()) {
		auto smallest = queue.top();
		queue.pop();

		output.write((char*)&(smallest.val), sizeof(uint64_t));
		if (smallest.pos >= smallest.max) continue;

		input.seekg(smallest.pos);
		uint64_t buf;

		input.read((char*)&buf, sizeof(uint64_t));
		queue.push({buf, smallest.pos + sizeof(uint64_t), smallest.max});
	}
}
