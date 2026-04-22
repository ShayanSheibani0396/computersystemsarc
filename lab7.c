/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "header.h"

// This is the function to fill in the data section.
void setupDataMemory(char* base_address,
                     unsigned int offset,
                     char *datasection,
                     unsigned int numberOfBytes){

    for(unsigned int i = 0; i < numberOfBytes; i++)
    {
        base_address[offset + i] = datasection[i];
    }
}
// This is the function to build I type instruction based on Instruction_storage
unsigned int buildIInstruction(unsigned char opcode,
                               unsigned char rs,
                               unsigned char rt,
                               int immediate){
    unsigned int machineCode = 0;
    unsigned int mask = 0;
    machineCode = immediate & 0x0000FFFF;
    mask = ((unsigned int)(rs & 0x000000FF)) << 21;
    machineCode = machineCode | mask;
    mask = ((unsigned int)(rt & 0x000000FF)) << 16;
    machineCode = machineCode | mask;
    mask = ((unsigned int)(opcode & 0x000000FF)) << 26;
    machineCode = machineCode | mask;
    //  machineCode should be OK now.
    return machineCode;  // finally return a 32-bit machine code.
}
// This is the function to build J type instruction based on Instruction_storage
unsigned int buildJInstruction(unsigned char opcode,
                               int immediate){
     unsigned int machineCode = 0;
     unsigned int mask = 0;
     machineCode = (opcode << 26) | (immediate & 0x03FFFFFF);





    return machineCode;  // finally return a 32-bit machine code.

}

// This is the function to build R type instruction based on Instruction_storage
unsigned int buildRInstruction(unsigned char opcode,
                               unsigned char rs,
                               unsigned char rt,
                               unsigned char rd,
                               unsigned char shamt,
                               unsigned char function){
    unsigned int machineCode = 0;
    machineCode = (opcode << 26) |
        (rs << 21) |
        (rt << 16) |
        (rd << 11) |
        (shamt << 6) |
        function;



    return machineCode;  // finally return a 32-bit machine code.

}
// This is the function to store the instructions.
void setupInstructionMemory( char* base_memory_address,
                                     int codeOffset,  // this is the code index.
                                     MIPS_Instruction *instructionStorage){
    int i = 0;
    unsigned int totalinstruction = 0;
    unsigned char opcode = 0;
    unsigned int machineCode = 0;
    do {
        // if la instruction.
        if (strcmp(instructionStorage[i].instruction, "la") == 0 ){
        // Notice: This instruction is already done as an example.

        // First, Answer this: what type of instruction is this? J, R or I instruction?
        // Answer:  I instruction

        // Secondly, what kind of machine language data format should it be?
        // Answer:  ooooooss sssttttt iiiiiiii iiiiiiii
        // needs:   opcode, rs, rt and immediate number as address.

        // Thirdly, what is the opcode of this instruction?
        // Answer:  0b101111;
            // Then combine the answer above and finish this part of the code.
            opcode = 0b101111;
            machineCode = buildIInstruction(opcode,
                                            instructionStorage[i].rs,
                                            instructionStorage[i].rt,
                                            instructionStorage[i].immediate);

            write_dword(base_memory_address, codeOffset+i*4, machineCode);
        }
        // lb
        else if (strcmp(instructionStorage[i].instruction, "lb") == 0 ){// if lb instruction.
        // First, Answer this: what type of instruction is this? J, R or I instruction?
        // Answer: I Instruction

        // Secondly, what kind of machine language data format should it be and what registers/numbers are needed?
        // Answer: oooooo sssss ttttt iiiiiiiiiiiiiiii
        // needs: opcode, rs, rt, immediate (offset)

        // Thirdly, what is the opcode of this instruction?
        // Answer: 0b100000

            // Then combine the answer above and finish this part of the code.

        opcode = 0b100000;

        machineCode = buildIInstruction(opcode,
                                            instructionStorage[i].rs,
                                            instructionStorage[i].rt,
                                            instructionStorage[i].immediate);

        write_dword(base_memory_address, codeOffset + i*4, machineCode);



        }
        // bge
        else if (strcmp(instructionStorage[i].instruction, "bge") == 0 ){// if bge instruction.
        // First, Answer this: what type of instruction is this? J, R or I instruction?
        // Answer: I instruction

        // Secondly, what kind of machine language data format should it be and what registers/numbers are needed?
        // Answer: oooooo sssss ttttt iiiiiiiiiiiiiiii
        // needs: opcode, rs, rt, immediate (branch offset)

        // Thirdly, what is the opcode of this instruction?
        // Answer: 0b000001

            // Then combine the answer above and finish this part of the code.

            opcode = 0b000001;
            machineCode = buildIInstruction(opcode,
                                            instructionStorage[i].rs,
                                            instructionStorage[i].rt,
                                            instructionStorage[i].immediate);

            write_dword(base_memory_address, codeOffset + i*4, machineCode);


        }
        //lw
        else if (strcmp(instructionStorage[i].instruction, "lw") == 0 ){// if lw instruction.
        // First, Answer this: what type of instruction is this? J, R or I instruction?
        // Answer: I instruction

        // Secondly, what kind of machine language data format should it be and what registers/numbers are needed?
        // Answer: ooooooss sssttttt iiiiiiii iiiiiiii
        // needs: opcode + rs + rt + immediate

        // Thirdly, what is the opcode of this instruction?
        // Answer: 0b100011

            // Then combine the answer above and finish this part of the code.

            opcode = 0b100011;

            machineCode = buildIInstruction(opcode,
                                            instructionStorage[i].rs,
                                            instructionStorage[i].rt,
                                            instructionStorage[i].immediate);

            write_dword(base_memory_address, codeOffset + i*4, machineCode);



        }
        // sw
        else if (strcmp(instructionStorage[i].instruction, "sw") == 0 ){// if sw instruction.
        // First, Answer this: what type of instruction is this? J, R or I instruction?
        // Answer: I instruction

        // Secondly, what kind of machine language data format should it be and what registers/numbers are needed?
        // Answer: oooooo sssss ttttt iiiiiiiiiiiiiiii
        // needs: opcode, rs, rt, immediate (offset)

        // Thirdly, what is the opcode of this instruction?
        // Answer: 0b101011

            // Then combine the answer above and finish this part of the code.

            opcode = 0b101011;
            machineCode = buildIInstruction(opcode,
                                            instructionStorage[i].rs,
                                            instructionStorage[i].rt,
                                            instructionStorage[i].immediate);

            write_dword(base_memory_address, codeOffset + i*4, machineCode);

        }
        // add (r-type)
		else if (strcmp(instructionStorage[i].instruction, "add") == 0 ){// if add instruction.
        // First, Answer this: what type of instruction is this? J, R or I instruction?
        // Answer: R instruction

        // Secondly, what kind of machine language data format should it be and what registers/numbers are needed?
        // Answer: oooooo sssss ttttt ddddd shamt funct
        // needs: opcode, rs, rt, rd, shamt, function

        // Thirdly, what is the opcode of this instruction?
        // Answer: 0

            // Then combine the answer above and finish this part of the code.

            opcode = 0;
            instructionStorage[i].function = 0b100000;
            machineCode = buildRInstruction(opcode,
                                            instructionStorage[i].rs,
                                            instructionStorage[i].rt,
                                            instructionStorage[i].rd,
                                            instructionStorage[i].shamt,
                                            instructionStorage[i].function);

            write_dword(base_memory_address, codeOffset + i*4, machineCode);

        }
        // addi
        else if (strcmp(instructionStorage[i].instruction, "addi") == 0 ){// if addi instruction.
        // First, Answer this: what type of instruction is this? J, R or I instruction?
        // Answer: I instruction

        // Secondly, what kind of machine language data format should it be and what registers/numbers are needed?
        // Answer: oooooo sssss ttttt iiiiiiiiiiiiiiii
        // needs: opcode, rs, rt, immediate

        // Thirdly, what is the opcode of this instruction?
        // Answer: 0b001000

            // Then combine the answer above and finish this part of the code.

           opcode = 0b001000;

            machineCode = buildIInstruction(opcode,
                                            instructionStorage[i].rs,
                                            instructionStorage[i].rt,
                                            instructionStorage[i].immediate);

            write_dword(base_memory_address, codeOffset + i*4, machineCode);



        }
        // j
        else if (strcmp(instructionStorage[i].instruction, "j") == 0 ){// if j instruction.
        // First, Answer this: what type of instruction is this? J, R or I instruction?
        // Answer: J Instruction

        // Secondly, what kind of machine language data format should it be and what registers/numbers are needed?
        // Answer: oooooo aaaaaaaaaaaaaaaaaaaaaaaaaa
        // needs: opcode, address

        // Thirdly, what is the opcode of this instruction?
        // Answer: 0b000010

            // Then combine the answer above and finish this part of the code.
            opcode = 0b000010;

            machineCode = buildJInstruction(opcode,
                                            instructionStorage[i].immediate);

            write_dword(base_memory_address, codeOffset + i*4, machineCode);




        }
        //end
        else if (strcmp(instructionStorage[i].instruction, "syscall") == 0 || // if end of the code
                 (strcmp(instructionStorage[i].instruction, "END") == 0 ))
        {
            // No need to worry about this. This is the end of code indicator.
            break;  // exit here.
        }
        i++;
    }while (1);
    totalinstruction = i;
}

// load the code into the memory starts from offset.
void loadCodeToMem(char *mem){
    // Finish this function in Lab 7. This lab would
    //  1. Parse the MIPS ASM file with parse_MIPS(); (this is already done )
    //     in main function. Data is already stored in array Data_storage[];
    //     Code is already stored into array Instruction_storage[].
    //  2. Store the data section into memory space starts from offset 0x2000 (8K)
    //  2. Convert all the instructions into 32-bit binary code based on MIPS instruction format.
    //  3. Store the code into memory starts from offset 0x0000. (beginning of the memory space)
    unsigned int dataSection = DATASECTION;
    unsigned int instructionSection = CODESECTION;
    // Starting from point 2 above.
    // Step 1: refer to the code in memory.c. Write Data_storage into memory space starting from 0x2000.
    setupDataMemory(mem,
                    dataSection,
                    Data_storage,
                    totalDataByte);

    // STEP 2: convert instructions into machine code (0x0000)
    setupInstructionMemory(mem,
                           instructionSection,
                           Instruction_storage);
    // Step 2: Convert all the instructions stored in
    //         Instruction_storage[] to binary code and store them into the memory starts at 0x0000
    // Just need to compile to following instructions:
    //         la, add, lb, bge, lw, sw, addi, j

	// Memory dump the information on the screen.
    puts("\n---- Data Section ----\n");
    memory_dump(mem, DATASECTION, 256);
    puts("\n---- Code Section ----\n");
    memory_dump(mem, CODESECTION, 256);

}
