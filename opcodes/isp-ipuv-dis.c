/* Single instruction disassembler for the ISP.

   Copyright (C) 2015-2017 Free Software Foundation, Inc.
   Contributed by NXP, ISP support.

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

   
   
#include "sysdep.h"
#include "dis-asm.h"
#include "isp-dis.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#define INSTR_BUFFER    4
#define    WORD_SIZE 	4 //bytes per word
//#define OPCODE_BUFFER   INSTR_BUFFER*4

#define BUF_SZ 200

static unsigned int  insn[INSTR_BUFFER];
char disasmBuffer[20];
char outbuff[BUF_SZ];

#define _1BYTE(v) (v&0xFF)
#define _2BYTE(v) ((v>>8)&0xFF)
#define _3BYTE(v) ((v>>16)&0xFF)
#define _4BYTE(v) ((v>>24)&0xFF)

#define BRANCH_COND(v) (_1BYTE(v))

#define RADDR(v) _2BYTE(v)

#define IM16(v) (v & 0xFFFF)
#define IM4(v)  (v & 0xF)


static const char* ixo[] = {"-", "o", "x", "xo", "i", "io", "ix", "ixo"};
#define IXO(v) (v & 7)
#define IXO_STR(v) (ixo[IXO(v)])

#define OP(v)       _3BYTE(v)
#define OPCODE(v)   _4BYTE(v)
#define OPC_OPCD(v)   (OPCODE(v) & 0x0F)
#define OPC_TYPE(v)   ((OPCODE(v) & 0xF0)>>4)
#define COND(v) (_1BYTE(v) & 0x0F)
#define RELADDR(v) ((char)(_2BYTE(v)))

#define DONE_IN(v) (_3BYTE(v))
#define CLZBITS(v) ( (_1BYTE(v) >> 4) & 0x7)
#define DEST(v) (_3BYTE(v))
#define IN1(v)  (_2BYTE(v)) 
#define IN2(v)  (_1BYTE(v)) 


static const char* scalar_regs[] = {
        "pc",	 "loopcnt",	"xpos",	 "ypos",  "confalu", "",	   "",       "",       "",      "",       "",        "",        "",        "",        "",      "",
        "in0",   "in1",     "in2",   "in3",	  "in4",     "in5",    "in6",    "in7",    "in8",   "in9",    "in10",    "in11",    "in12",    "in13",    "in14",  "in15",
        "in16",	 "in17",	"in18",	 "in19",  "in20",	 "in21",   "in22",   "in23",   "in24",	"in25",   "in26",	 "in27",	"in28",	   "in29",	  "in30",  "in31",
        "in32",	 "in33",	"in34",	 "in35",  "in36",	 "in37",   "in38",	 "in39",   "maskv", "maskvq", "vflag_o", "vflag_c", "vflag_n", "vflag_z", "",	   "", 
        "out0",	 "out1",	"out2",  "out3",  "out4",    "out5",   "out6",	 "out7",   "out8",	"out9",   "out10",	 "out11",   "",		   "",		  "",	   "",	
        "gpr0",	 "gpr1",    "gpr2",	 "gpr3",  "gpr4",	 "gpr5",   "gpr6",	 "gpr7",   "gpr8",	"gpr9",   "gpr10",	 "gpr11",	"gpr12",   "gpr13",   "gpr14", "gpr15",
        "gpr16", "gpr17",   "gpr18", "gpr19", "gpr20",   "gpr21",  "gpr22",  "gpr23",  "gpr24", "gpr25",  "gpr26",   "gpr27",   "gpr28",   "gpr29",   "gpr30", "gpr31",
        "acc0",	 "acc1",    "acc2",  "acc3",  "acc4",    "acc5",   "acc6",   "acc7",   "",	    "",       "",        "",        "",        "",  	  "",	   "",
        "sacc0", "sacc1",   "sacc2", "sacc3", "sacc4",   "sacc5",  "sacc6",  "sacc7",  "",      "",	      "",        "",        "",        "",	      "",      "",
        "opixa", "opix",    "",      "",      "",        "",       "",       "",       "",      "",       "",        "",        "",        "",        "",      "",
        "abs0",	 "abs1",    "abs2",  "abs3",  "angle0",  "angle1", "angle2", "angle3", "",      "",       "",        "",        "", 	   "",	      "",	   "",
		"",		 "",		"",		 "",	  "",		 "",	   "",		 "",	   "",		"",       "",        "",		"",		   "",		  "",	   "",
		"",		 "",		"",		 "",	  "",		 "",	   "",		 "",	   "",		"",		  "",		 "",		"",		   "",		  "",	   "",
		"",		 "",		"",		 "",	  "",		 "",	   "",		 "",	   "",		"",		  "",		 "",		"",		   "",		  "",	   "",
		"",		 "",		"",      "",	  "",		 "",	   "",		 "",	   "",		"",		  "",		 "",		"",		   "",		  "",	   "",
		"",		 "",		"",      "",	  "",		 "",	   "",		 "",	   "",		"",		  "",		 "",	    "lock",    "",	      "one",   "zero"
};

static const char* vector_regs[] = {
        "vv0",      "vv1",      "vv2",      "vv3",      "vv4",      "vv5",      "vv6",      "vv7",      "vv8",      "vv9",      "vv10",     "vv11",     "vv12",     "vv13",     "vv14",     "vv15",
        "vh0",      "vh1",      "vh2",      "vh3",      "vh4",      "vh5",      "vh6",      "vh7",      "vh8",      "vh9",      "vh10",     "vh11",     "vh12",     "vh13",     "vh14",     "vh15",
        "vh16",     "vh17",     "vh18",     "vh19",     "vh20",     "vh21",     "vh22",     "vh23",     "vh24",     "",         "",         "",         "",         "vout0",    "vout1",    "vout2",
        "vgrpr0",   "vgpr1",    "vgpr2",    "vgpr3",    "vgpr4",    "vgpr5",    "vgpr6",    "vgpr7",    "vacc0",    "vacc1",    "vsacc0",   "vsacc1",   "vabs",     "vangle",   "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",
        "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "",         "vone",     "vzero"
};

static const char* branch_inst[] = {
        "bal", "bnv", "beq", "bne",
        "bcc", "bcs", "bmi", "bpl",
        "bos", "boc", "bqe", "blt",
        "bhi", "bls", "bgt", ""
};

static const char* common_inst[] = {
		"mov", "add", "sub", "abd",
		"mulh", "mull", "", "and",
		"or", "xor", "min", "max",
		"asr", "lsr", "asl", "lsl"
};


char* ipuvDummyInstruction_dis()
{
    sprintf(outbuff, "Unknown");
    return outbuff;
}

#define OFFSET(addr, v) (addr + RELADDR(v)*4)

char* ipuvFlow(unsigned ins, bfd_vma addr, disassemble_info *info){
    bfd_byte opcode = OPC_OPCD(ins);
    if (ins == 0){
        sprintf(outbuff, "nop");
        return outbuff;
    }else if (ins == 1){
        sprintf(outbuff, "halt");
        return outbuff;
    }else if (ins == 2){
        sprintf(outbuff, "dbg");
        return outbuff;
    }
    
    switch(opcode){
        case 0x2:
            sprintf(outbuff, "done %x,%s", addr + RELADDR(ins), IXO_STR(ins));
            break;
        case 0x3:
            sprintf(outbuff, "dout %s,%x,%s", scalar_regs[DONE_IN(ins)], OFFSET(addr,ins), IXO_STR(ins));
            break;
        case 0x4:
            sprintf(outbuff, "dvot %s,%x,%s", vector_regs[DONE_IN(ins)], OFFSET(addr,ins), IXO_STR(ins));
            break;
        case 0x6:
            sprintf(outbuff, "loop %x", OFFSET(addr,ins));
            break;
        case 0x7://branch
            sprintf(outbuff, "%s %x",branch_inst[COND(ins)], OFFSET(addr,ins));
            break;
        case 0xA:
            sprintf(outbuff, "ldon %x,%s", OFFSET(addr,ins), IXO_STR(ins));
            break;
        case 0xB:
            sprintf(outbuff, "ldot %s,%x,%s", scalar_regs[DONE_IN(ins)], OFFSET(addr,ins), IXO_STR(ins));
            break;
        case 0xC:
            sprintf(outbuff, "ldvo %s,%x,%s", vector_regs[DONE_IN(ins)], OFFSET(addr,ins), IXO_STR(ins));
            break;
        default:
            return ipuvDummyInstruction_dis();
    }
    
    return outbuff;
}


char* ipuvCLZ(unsigned ins, bfd_vma addr, disassemble_info *info){
    bfd_byte clz = CLZBITS(ins);
    switch(clz){
        case  0x1:
            sprintf(outbuff, "clz %s,%s", scalar_regs[DEST(ins)], scalar_regs[IN1(ins)]);
            break;
        case 0x4:
            sprintf(outbuff, "clz %s,%s", scalar_regs[DEST(ins)], vector_regs[IN1(ins)]);
            break;
        case 0x6:
            sprintf(outbuff, "clz %s,%s", vector_regs[DEST(ins)], vector_regs[IN1(ins)]);
            break;
        default:
            return ispDummyInstruction_dis();
    }
    return outbuff;
}


char* ipuvS_SxI(unsigned ins, bfd_vma addr, disassemble_info *info){
    bfd_byte opcode = OPC_OPCD(ins);
    
    switch(opcode){
        case 0xF:
            if (CLZBITS(ins))
                return ipuvCLZ(ins, addr, info);
        case 0xE:
        case 0xD:
        case 0xC:
            sprintf(outbuff, "%s %s,%s,%x", common_inst[opcode], scalar_regs[DEST(ins)], scalar_regs[IN1(ins)], IM4(ins));
            break;
        case 0x0:
        	sprintf(outbuff, "%s %s,%x", common_inst[opcode], scalar_regs[DEST(ins)], IM16(ins));
        	break;
        default:
        	sprintf(outbuff, "%s %s,%x", common_inst[opcode], scalar_regs[DEST(ins)], IM16(ins));
    }
    
    return outbuff;
}

char* ipuvS_SxS(unsigned ins, bfd_vma addr, disassemble_info *info){
    bfd_byte opcode = OPC_OPCD(ins);
    
    switch(opcode){
    	case 0x0:
    		sprintf(outbuff, "%s %s,%s", common_inst[opcode], scalar_regs[DEST(ins)], scalar_regs[IN2(ins)]);
    		break;
    	default:
    		sprintf(outbuff, "%s %s,%s,%s", common_inst[opcode], scalar_regs[DEST(ins)], scalar_regs[IN1(ins)], scalar_regs[IN2(ins)]);
    }

    return outbuff;
}

char* ipuvS_VxS(unsigned ins, bfd_vma addr, disassemble_info *info){
    bfd_byte opcode = OPC_OPCD(ins);
    
    switch(opcode){
    	case 0x0:
    		sprintf(outbuff, "%s %s,%x", common_inst[opcode], scalar_regs[DEST(ins)], IM16(ins));
    		break;
    	default:
    		sprintf(outbuff, "%s %s,%s,%s", common_inst[opcode], scalar_regs[DEST(ins)], vector_regs[IN1(ins)], scalar_regs[IN2(ins)]);
    }

    return outbuff;
}

char* ipuvS_VxV(unsigned ins, bfd_vma addr, disassemble_info *info){
    bfd_byte opcode = OPC_OPCD(ins);
    
    switch(opcode){
    	case 0x0:
    		sprintf(outbuff, "%s %s,%s", common_inst[opcode], scalar_regs[DEST(ins)], vector_regs[IN2(ins)]);
    		break;
    	default:
    		sprintf(outbuff, "%s %s,%s,%s", common_inst[opcode], scalar_regs[DEST(ins)], vector_regs[IN1(ins)], vector_regs[IN2(ins)]);
    }

    return outbuff;
}

char* ipuvV_VxS(unsigned ins, bfd_vma addr, disassemble_info *info){
    bfd_byte opcode = OPC_OPCD(ins);
    
    sprintf(outbuff, "%s %s,%s,%s", common_inst[opcode], vector_regs[DEST(ins)], vector_regs[IN1(ins)], scalar_regs[IN2(ins)]);
    return outbuff;
}

char* ipuvV_VxV(unsigned ins, bfd_vma addr, disassemble_info *info){
    bfd_byte opcode = OPC_OPCD(ins);
    
    switch(opcode){
    	case 0x0:
    		sprintf(outbuff, "%s %s,%s", common_inst[opcode], vector_regs[DEST(ins)], vector_regs[IN2(ins)]);
    		break;
    	default:
    		sprintf(outbuff, "%s %s,%s,%s", common_inst[opcode], vector_regs[DEST(ins)], vector_regs[IN1(ins)], vector_regs[IN2(ins)]);
    }
    return outbuff;
}

/* Print the ISP instruction at address addr in debugged memory,
   on info->stream. Return length of the instruction, in bytes.  */
char* ipuvDisassemle(unsigned ins, bfd_vma addr, disassemble_info *info){

    bfd_byte type = OPC_TYPE(ins);
    bfd_byte opcode = OPC_OPCD(ins);
    
    switch(type){
        case 0x0:
            return ipuvFlow(ins, addr, info);
        case 0x1:
            return ipuvS_SxI(ins, addr, info);
        case 0x2:
            return ipuvS_SxS(ins, addr, info);
        case 0x4:
            return ipuvS_VxS(ins, addr, info);
        case 0x5:
            return ipuvS_VxV(ins, addr, info);
        case 0x6:
            return ipuvV_VxS(ins, addr, info);
        case 0x7:
            return ipuvV_VxV(ins, addr, info);
    }
    

    return ispDummyInstruction_dis();
}

int
print_insn_isp_ipuv (bfd_vma addr, disassemble_info *info)
{
    bfd_byte buffer [WORD_SIZE];
    int status,i;
    int buf_size = sizeof(buffer);
    if (info->buffer_length) {
        if (addr+buf_size > (info->buffer_vma+info->buffer_length)) {
            buf_size = (info->buffer_vma+info->buffer_length)-addr;
            if (buf_size > WORD_SIZE){buf_size = WORD_SIZE;}
            memset(buffer,0,buf_size);
        }
    }

    /* Reading byte by byte. read_memory_funct got
     * a feature pass NO error if only first byte
     * possible to read and the other are unaccessible*/

    for (i=0;i<buf_size;i++){
    	bfd_byte* _link = &buffer[i];
		 status = (*info->read_memory_func) (addr++, _link, 1, info);
		 if (status != 0) {
			 //(*info->memory_error_func) (status, addr, info);
			 return -1;
		 }
    }

    insn[0] = bfd_getl32 (buffer);


    (*info->fprintf_func) (info->stream, (ipuvDisassemle(insn[0], addr, info)) );

    //Instruction size
    return 4;
}
