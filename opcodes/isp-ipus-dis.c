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
#define RT(v) _3BYTE(v)
#define RA(v) _2BYTE(v)
#define RB(v) _1BYTE(v)

#define IM16(v) (v & 0xFFFF)
#define IM4(v)  (v & 0xF)

#define VT(v)   _3BYTE(v)
#define VA(v)   _2BYTE(v)
#define VB(v)   _1BYTE(v)

#define MA(v) (_3BYTE(v) & 0x07)

static const char* min[] = { "w", "ina", "ww", "inb", "mzero"};
#define M_IN(v) (v & 0x7)
#define M_IN_STR(v) (min[M_IN(v)])

static const char* maskin[] = {"w", "inalpha", "ww", "reserved"};
#define MASK(v) (v & 3)
#define MASK_STR(v) (maskin[MASK(v)])

static const char* ixo[] = {"-", "o", "x", "xo", "i", "io", "ix", "ixo"};
#define IXO(v) (v & 7)
#define IXO_STR(v) (ixo[IXO(v)])

#define OP(v)       _3BYTE(v)
#define OPCODE(v)   _4BYTE(v)
#define OPC_TYPE(v)   (OPCODE(v) & 0x0F)
#define OPC_OPCD(v)   ((OPCODE(v) & 0xF0)>>4)
#define OP_MOV  0
#define OP_ADD  1
#define OP_SUB  2
#define OP_ABD  3
#define OP_MULH 4
#define OP_MULL 5
#define OP_AND  7
#define OP_OR   8
#define OP_XOR  9
#define OP_MIN  10
#define OP_MAX  11
#define OP_ASR  12
#define OP_LSR  13
#define OP_ASL  14
#define OP_CLZ  15
#define OP_LSL  15


static const char* ipus_regs[] = {
		"pc",			//0
		"loopcnt",		//1
		"xpos",			//2
		"ypos",			//3
		"confalu",		//4
		"",			//5
		"",			//6
		"",			//7
		"confaddt",		//8
		"confthres",	//9
		"confsort",		//10
		"confbest",		//11
		"confhist",		//12
		"confstat",		//13
		"",			//14
		"",			//15
		"ina0",			//16
		"ina1",			//17
		"ina2",			//18
		"ina3",			//19
		"ina4",			//20
		"ina5",			//21
		"ina6",			//22
		"ina7",			//23
		"ina8",			//24
		"",			//25
		"",			//26
		"",			//27
		"",			//28
		"",			//29
		"",			//30
		"",			//31
		"inb0",			//32
		"inb1",			//33
		"inb2",			//34
		"inb3",			//35
		"inb4",			//36
		"inb5",			//37
		"inb6",			//38
		"inb7",			//39
		"inb8",			//40
		"",			//41
		"",			//42
		"",			//43
		"",			//44
		"",			//45
		"",			//46
		"",			//47
		"inalpha0",		//48
		"inalpha1",		//49
		"inalpha2",		//50
		"inalpha3",		//51
		"inalpha4",		//52
		"inalpha5",		//53
		"inalpha6",		//54
		"inalpha7",		//55
		"inalpha8",		//56
		"",			//57
		"",			//58
		"",			//59
		"",			//60
		"",			//61
		"",			//62
		"",			//63
		"w0",			//64
		"w1",			//65
		"w2",			//66
		"w3",			//67
		"w4",			//68
		"w5",			//69
		"w6",			//70
		"w7",			//71
		"w8",			//72
		"",			//73
		"",			//74
		"",			//75
		"",			//76
		"",			//77
		"",			//78
		"",			//79
		"w20",			//80
		"w21",			//81
		"w22",			//82
		"w23",			//83
		"w24",			//84
		"w25",			//85
		"w26",			//86
		"w27",			//87
		"w28",			//88
		"",			//89
		"",			//90
		"",			//91
		"",			//92
		"",			//93
		"",			//94
		"",			//95
		"mask0",		//96
		"mask1",		//97
		"mask2",		//98
		"mask3",		//99
		"mask4",		//100
		"mask5",		//101
		"mask6",		//102
		"mask7",		//103
		"mask8",		//104
		"maskv",		//105
		"nhood",		//106
		"",			//107
		"mflag_o",		//108
		"mflag_c",		//109
		"mflag_n",		//110
		"mflag_z",		//111
		"gpr0",			//112
		"gpr1",			//113
		"gpr2",			//114
		"gpr3",			//115
		"gpr4",			//116
		"gpr5",			//117
		"gpr6",			//118
		"gpr7",			//119
		"gpr8",			//120
		"gpr9",			//121
		"gpr10",		//122
		"gpr11",		//123
		"gpr12",		//124
		"gpr13",		//125
		"gpr14",		//126
		"gpr15",		//127
		"out0",			//128
		"out1",			//129
		"out2",			//130
		"out3",			//131
		"",			//132
		"",			//133
		"",			//134
		"",			//135
		"",			//136
		"",			//137
		"",			//138
		"",			//139
		"",			//140
		"",			//141
		"",			//142
		"",			//143
		"opixa0",		//144
		"opix0",		//145
		"opixa1",		//146
		"opix1",		//147
		"",			//148
		"",			//149
		"",			//150
		"",			//151
		"acc0",			//152
		"acc1",			//153
		"acc2",			//154
		"acc3",			//155
		"sacc0",		//156
		"sacc1",		//157
		"sacc2",		//158
		"sacc3",		//159
		"sum",			//160
		"clipped",		//161
		"threshold",	//162
		"scaled",		//163
		"maximum",		//164
		"minimum",		//165
		"median",		//166
		"argmin",		//167
		"argmax",		//168
		"",			//169
		"",			//170
		"",			//171
		"",			//172
		"",			//173
		"",			//174
		"",			//175
		"",			//176
		"",			//177
		"",			//178
		"",			//179
		"",			//180
		"",			//181
		"",			//182
		"",			//183
		"",			//184
		"",			//185
		"",			//186
		"",			//187
		"",			//188
		"",			//189
		"",			//190
		"",			//191
		"",			//192
		"",			//193
		"",			//194
		"",			//195
		"",			//196
		"",			//197
		"",			//198
		"",			//199
		"",			//200
		"",			//201
		"",			//202
		"",			//203
		"",			//204
		"",			//205
		"",			//206
		"",			//207
		"luta",			//208
		"lutv",			//209
		"",			//210
		"",			//211
		"hbina",		//212
		"hbinadd",		//213
		"hbinincl",		//214
		"hbininch",		//215
		"sf0datal",		//216
		"sf0datah",		//217
		"sf1datal",		//218
		"sf1datah",		//219
		"sf2datal",		//220
		"sf2datah",		//221
		"sf3datal",		//222
		"sf3datah",		//223
		"srec",			//224
		"",			//225
		"",			//226
		"",			//227
		"",			//228
		"",			//229
		"",			//230
		"",			//231
		"",			//232
		"",			//233
		"",			//234
		"",			//235
		"",			//236
		"",			//237
		"",			//238
		"",			//239
		"soin",			//240
		"soclear",		//241
		"so0",			//242
		"so1",			//243
		"so2",			//244
		"so3",			//245
		"so4",			//246
		"soa0",			//247
		"soa1",			//248
		"soa2",			//249
		"soa3",			//250
		"soa4",			//251
		"lock",			//252
		"prng",			//253
		"one",			//254
		"zero"			//255
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


bfd_vma getOffsettAddr(bfd_vma addr, bfd_vma offset);
bfd_vma getOffsettAddr(bfd_vma addr, bfd_vma offset){
	return addr + (char)offset*4;//offset is always in signed byte
}


char* ispDummyInstruction_dis();
char* ispDummyInstruction_dis()
{
    sprintf(outbuff, "Unknown");
    return outbuff;
}


char* ispDoneDout(unsigned ins, bfd_vma addr, disassemble_info *info);
char* ispDoneDout(unsigned ins, bfd_vma addr, disassemble_info *info){
    
    unsigned int a = getOffsettAddr(addr, RADDR(ins));
    int cmd = OPCODE(ins);
    
    if (cmd == 2){
        sprintf(outbuff, "done x%x", a);
    }else if (cmd == 3){
        sprintf(outbuff, "dout %s,x%x",ipus_regs[OP(ins)], a);
    }else if (cmd == 10){
        sprintf(outbuff, "ldon x%x", a);
    }else if (cmd == 11){
        sprintf(outbuff, "ldot %s,x%x",ipus_regs[OP(ins)], a);
    }else{       
        sprintf(outbuff,"unknown opcode");
        return outbuff;
    }
    
    if (ins & 0xF)
        strcat(outbuff, IXO_STR(ins));
    
    return outbuff;
}



/* Print the ISP instruction at address addr in debugged memory,
   on info->stream. Return length of the instruction, in bytes.  */
char* ispDisassemle(unsigned ins, bfd_vma addr, disassemble_info *info);
char* ispDisassemle(unsigned ins, bfd_vma addr, disassemble_info *info){

    bfd_byte opcode = OPCODE(ins);
    switch (opcode)
    {
    	case 0x0:
    		if (ins == 0){
    			sprintf(outbuff, "nop");
    			return outbuff;
    		}else if (ins == 1){
    			sprintf(outbuff, "halt");
    			return outbuff;
    		}
    		break;
    	case 0x2:
    	case 0x3:
    	case 0xA:
    	case 0xB:
    		return ispDoneDout(ins, addr, info);
    		break;
    	case 0x6:
    		sprintf(outbuff, "loop x%x", (unsigned int)getOffsettAddr(addr, RADDR(ins)));
    		return outbuff;
    		break;
    	case 0x7:
    		sprintf(outbuff, "%s x%x", branch_inst[BRANCH_COND(ins)], (unsigned int)getOffsettAddr(addr, RADDR(ins)));
    		return outbuff;
    		break;
        case 0x1F:
            if (_1BYTE(ins) == 0x10){//clz bit
                sprintf(outbuff, "clz %s, %s", ipus_regs[RT(ins)], ipus_regs[RA(ins)]);
                return outbuff;
            }else{
                sprintf(outbuff, "lsl %s,%s,%02x", ipus_regs[RT(ins)], ipus_regs[RA(ins)], IM4(ins));
                return outbuff;
            }
            break;
        case 0x5F:
        	if (_1BYTE(ins) == 0x10){//clz bit
        		sprintf(outbuff, "clz w,%s", M_IN_STR(RT(ins)));
        		return outbuff;
        	}
        	break;
    	case 0x76:
    		sprintf(outbuff, "swp");
    		return outbuff;
    		break;
        case 0x1E:
        case 0x1C:
        case 0x1D:
            sprintf(outbuff, "%s %s,%s,x%x", common_inst[OPC_TYPE(ins)], ipus_regs[RT(ins)], ipus_regs[RA(ins)], IM4(ins));
            return outbuff;
    }
    
    bfd_byte opcd= OPC_OPCD(ins);
    bfd_byte type = OPC_TYPE(ins);
    switch(type)
    {
        case 0x0://mset
            if (opcd == 3){
            	sprintf(outbuff, "%s x%x", "mset", IM16(ins));
            	return outbuff;
            } else if (opcd == 4){
                sprintf(outbuff, "%s %s", "mset", ipus_regs[RB(ins)]);
                return outbuff;
            }         
            break;
        case 0x1://mset
            if (opcd == 3){
                sprintf(outbuff, "%s %s,x%x", "mset", MASK_STR(RT(ins)),IM16(ins));
                return outbuff;
            }else if (opcd == 4){
                sprintf(outbuff, "%s %s,%s", "mset", MASK_STR(RT(ins)), ipus_regs[RB(ins)]);
                return outbuff;
            }
            break;
        case 0x2://minv
            if (opcd == 3){
                sprintf(outbuff, "minv");
                return outbuff;
            }
            break;
        case 0x3://absdiff
        	if (opcd == 5){
        		sprintf(outbuff, "%s w,%s,x%x", "absdiff", M_IN_STR(RT(ins)), IM16(ins));
        		return outbuff;
        	}else if (opcd == 6){
        		sprintf(outbuff, "%s w,%s,%s", "absdiff", M_IN_STR(RT(ins)), ipus_regs[RB(ins)]);
        		return outbuff;
        	}else if (opcd == 7){
        		sprintf(outbuff, "%s w,%s,%s", "absdiff", M_IN_STR(RT(ins)), M_IN_STR(RB(ins)));
        		return outbuff;
        	}
        	break;
        case 0x4://mthr &thf
            if (opcd == 3){
                sprintf(outbuff, "%s %s,x%x", "mthr", MASK_STR(RT(ins)), IM16(ins));
                return outbuff;
            }else if (opcd == 4){
                sprintf(outbuff, "%s %s,%s", "mthr", MASK_STR(RT(ins)), ipus_regs[RB(ins)]);
                return outbuff;
            }else if (opcd == 5){
                sprintf(outbuff, "%s w,%s,x%x", "thf", M_IN_STR(RT(ins)), IM16(ins));
                return outbuff;
            }else if (opcd == 6){
                sprintf(outbuff, "%s w,%s,%s", "thf", M_IN_STR(RT(ins)), ipus_regs[RB(ins)]);
                return outbuff;
            }else if (opcd == 7){
                sprintf(outbuff, "%s w,%s,%s", "thf", M_IN_STR(RT(ins)), M_IN_STR(RB(ins)));
                return outbuff;
            }
            break;
        case 0x5://mith&thm
            if (opcd == 3){
                sprintf(outbuff, "%s %s,x%x", "mith", MASK_STR(RT(ins)), IM16(ins));
                return outbuff;
            }else if (opcd == 4){
                sprintf(outbuff, "%s %s,%s", "mith", MASK_STR(RT(ins)), ipus_regs[RB(ins)]);
                return outbuff;
            }else if (opcd == 5){
                sprintf(outbuff, "%s w,%s,x%x", "thm", M_IN_STR(RT(ins)), IM16(ins));
                return outbuff;
            }else if (opcd == 6){
                sprintf(outbuff, "%s w,%s,%s", "thm", M_IN_STR(RT(ins)), ipus_regs[RB(ins)]);
                return outbuff;
            }else if (opcd == 7){
                sprintf(outbuff, "%s w,%s,%s", "thm", M_IN_STR(RT(ins)), M_IN_STR(RB(ins)));
                return outbuff;
            }
            break;
        case 0x7://mand
            if (opcd == 3){
                sprintf(outbuff, "%s x%x", "mand", IM16(ins));
                return outbuff;
            }else if (opcd == 4){
                sprintf(outbuff, "%s %s", "mand", ipus_regs[RB(ins)]);
                return outbuff;
            }
            break;
    }
    
    
    switch(type)
    {
        case OP_MOV:
            if (opcd == 1){
            	sprintf(outbuff, "%s %s,x%x", common_inst[OP_MOV], ipus_regs[RT(ins)], IM16(ins));
            	return outbuff;
            }else if (opcd == 2){
            	sprintf(outbuff, "%s %s,%s", common_inst[OP_MOV], ipus_regs[RT(ins)], ipus_regs[RB(ins)]);
            	return outbuff;
            }else if (opcd == 5){
            	sprintf(outbuff, "%s w,x%x", common_inst[OP_MOV], IM16(ins));
            	return outbuff;
            }else if (opcd == 6){
            	sprintf(outbuff, "%s w,%s", common_inst[OP_MOV], ipus_regs[RB(ins)]);
            	return outbuff;
            }else if (opcd == 7){
            	sprintf(outbuff, "%s w,%s", common_inst[OP_MOV], M_IN_STR(RB(ins)));
            	return outbuff;
            }else
            	return ispDummyInstruction_dis();
            break;
        default:
            if (opcd == 1){
        		sprintf(outbuff, "%s %s,x%x", common_inst[type], ipus_regs[RT(ins)], IM16(ins));
        		return outbuff;
            }else if (opcd == 2){
        		sprintf(outbuff, "%s %s,%s,%s", common_inst[type], ipus_regs[RT(ins)], ipus_regs[RA(ins)], ipus_regs[RB(ins)]);
        		return outbuff;
            }else if (opcd == 5){
        		sprintf(outbuff, "%s w,%s,x%x", common_inst[type], M_IN_STR(RT(ins)), IM16(ins));
        		return outbuff;
            }else if (opcd == 6){
        		sprintf(outbuff, "%s w,%s,%s", common_inst[type], M_IN_STR(RT(ins)), ipus_regs[RB(ins)]);
        		return outbuff;
            }else if (opcd == 7){
        		sprintf(outbuff, "%s w,%s,%s", common_inst[type], M_IN_STR(RT(ins)), M_IN_STR(RB(ins)));
        		return outbuff;
            }
    }

    return ispDummyInstruction_dis();
}

int
print_insn_isp_ipus (bfd_vma addr, disassemble_info *info)
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


    (*info->fprintf_func) (info->stream, (ispDisassemle(insn[0], addr, info)) );
    
    //Instruction size
    return 4;
}

