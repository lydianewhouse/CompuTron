#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "computron.h"

TEST_CASE("Test load_from_file", "[CompuTron]")
{
    //Test read from file
    std::array<int, memorySize> memory{ 0 };
    int accumulator{ 0 };
    size_t instructionCounter{ 0 };
    int instructionRegister{ 0 };
    size_t operationCode{ 0 };
    size_t operand{ 0 };

    const std::vector<int> inputs{ 4, 5 };

    load_from_file(memory, "p1.txt");

    REQUIRE(memory[0] == 1007);
    REQUIRE(memory[1] == 1008);
    REQUIRE(memory[2] == 2007);
    REQUIRE(memory[3] == 3008);
    REQUIRE(memory[4] == 2109);
    REQUIRE(memory[5] == 1109);
    REQUIRE(memory[6] == 4300);
}

//TEST_CASE("Test opCodeToCommand", "[CompuTron]")
//{
//    REQUIRE(opCodeToCommand(10) == Command::read);
//    REQUIRE(opCodeToCommand(11) == Command::write);
//    REQUIRE(opCodeToCommand(20) == Command::load);
//    REQUIRE(opCodeToCommand(21) == Command::store);
//    REQUIRE(opCodeToCommand(30) == Command::add);
//    REQUIRE(opCodeToCommand(31) == Command::subtract);
//    REQUIRE(opCodeToCommand(32) == Command::divide);
//    REQUIRE(opCodeToCommand(33) == Command::multiply);
//    REQUIRE(opCodeToCommand(40) == Command::branch);
//    REQUIRE(opCodeToCommand(41) == Command::branchNeg);
//    REQUIRE(opCodeToCommand(42) == Command::branchZero);
//    REQUIRE(opCodeToCommand(43) == Command::halt);
//
//
//
//}

TEST_CASE("Test Execute (Add)", "[CompuTron]")
{
    //Test read from file
    std::array<int, memorySize> memory{ 0 };
    int accumulator{ 0 };
    size_t instructionCounter{ 0 };
    int instructionRegister{ 0 };
    size_t operationCode{ 0 };
    size_t operand{ 0 };

    const std::vector<int> inputs{ 4, 5 };

    load_from_file(memory, "p1.txt");

    execute(memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand, inputs);


    REQUIRE(memory[7] == 4);
    REQUIRE(memory[8] == 5);
    REQUIRE(memory[9] == 9);
}

TEST_CASE("Test Subtract", "[CompuTron]")
{
    //Test read from file
    std::array<int, memorySize> memory{ 1007, 1008, 2007, 3108, 2109, 1109, 4300, 0000, 0000, 0000};

    int accumulator{ 0 };
    size_t instructionCounter{ 0 };
    int instructionRegister{ 0 };
    size_t operationCode{ 0 };
    size_t operand{ 0 };

    const std::vector<int> inputs{ 4, 5 };

    execute(memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand, inputs);


    REQUIRE(memory[7] == 4);
    REQUIRE(memory[8] == 5);
    REQUIRE(memory[9] == -1);


}

TEST_CASE("Test Multiply", "[CompuTron]")
{
    //Test read from file
    std::array<int, memorySize> memory{ 1007, 1008, 2007, 3308, 2109, 1109, 4300, 0000, 0000, 0000 };

    int accumulator{ 0 };
    size_t instructionCounter{ 0 };
    int instructionRegister{ 0 };
    size_t operationCode{ 0 };
    size_t operand{ 0 };

    const std::vector<int> inputs{ 4, 5 };

    execute(memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand, inputs);


    REQUIRE(memory[7] == 4);
    REQUIRE(memory[8] == 5);
    REQUIRE(memory[9] == 20);


}

TEST_CASE("Test Divide", "[CompuTron]")
{
    //Test read from file
    std::array<int, memorySize> memory{ 1007, 1008, 2007, 3208, 2109, 1109, 4300, 0000, 0000, 0000 };

    int accumulator{ 0 };
    size_t instructionCounter{ 0 };
    int instructionRegister{ 0 };
    size_t operationCode{ 0 };
    size_t operand{ 0 };

    const std::vector<int> inputs{ 10, 5 };

    execute(memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand, inputs);


    REQUIRE(memory[7] == 10);
    REQUIRE(memory[8] == 5);
    REQUIRE(memory[9] == 2);


}

TEST_CASE("Test Divide By Zero", "[CompuTron]")
{
    //Test read from file
    std::array<int, memorySize> memory{ 1007, 1008, 2007, 3208, 2109, 1109, 4300, 0000, 0000, 0000 };

    int accumulator{ 0 };
    size_t instructionCounter{ 0 };
    int instructionRegister{ 0 };
    size_t operationCode{ 0 };
    size_t operand{ 0 };

    const std::vector<int> inputs{ 10, 0 };

    REQUIRE_THROWS(execute(memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand, inputs));

}








