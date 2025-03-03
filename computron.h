//computron.h
#ifndef COMPUTRON_H
#define COMPUTRON_H
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <stdexcept>

constexpr size_t memorySize{100};
constexpr int minWord{-9999};
constexpr int maxWord{9999};

enum class Command{
   read=10, write=11,
   load=20, store=21,
   add=30, subtract=31, divide=32, multiply=33,
   branch=40, branchNeg=41, branchZero=42, halt=43
};

void load_from_file(std::array<int, memorySize>& memory, const std::string& filename);

void execute(std::array<int, memorySize>& memory, int* const acPtr, 
            size_t* const icPtr, int* const irPtr, 
            size_t* const opCodePtr, size_t* const opPtr,
            const std::vector<int>& inputs);

void dump(std::array<int, memorySize>&memory, int accumulator, 
         size_t instructionCounter, size_t instructionRegister,
         size_t operationCode, size_t operand);

bool validWord(int word);

void output(std::string label, int width, int value, bool sign);

#endif