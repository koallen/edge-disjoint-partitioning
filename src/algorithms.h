#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_
#include <string>
#include <unordered_set>
#include "index.h"

Index RunAlgorithmOne(std::string& input_filename, uint32_t num_of_labels);
uint32_t RunAlgorithmTwo(Index& index, uint32_t src, uint32_t dst, std::unordered_set<uint32_t>& labels);
#endif
