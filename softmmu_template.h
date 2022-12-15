/*
 *  Software MMU support
 *
 * Generate helpers used by TCG for qemu_ld/st ops and code load
 * functions.
 *
 * Included from target op helpers and exec.c.
 *
 *  Copyright (c) 2003 Fabrice Bellard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */
#include "qemu-timer.h"
#include <time.h>
//#define UARTLOW 0xffffffffb40003f8
//#define UARTHI  0xffffffffb40003ff
#define UARTLO  0xffffffffb80003f8
#define UARTHI  0xffffffffb80003ff
extern int ayaz;
extern int ayaz2;
extern int glob_e1000_int;
extern int glob_uart_int;
extern CPUState * envArray[12];
extern int state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,state12;
#define DATA_SIZE (1 << SHIFT)

#if DATA_SIZE == 8
#define SUFFIX q
#define USUFFIX q
#define DATA_TYPE uint64_t
#elif DATA_SIZE == 4
#define SUFFIX l
#define USUFFIX l
#define DATA_TYPE uint32_t
#elif DATA_SIZE == 2
#define SUFFIX w
#define USUFFIX uw
#define DATA_TYPE uint16_t
#elif DATA_SIZE == 1
#define SUFFIX b
#define USUFFIX ub
#define DATA_TYPE uint8_t
#else
#error unsupported data size
#endif

#ifdef SOFTMMU_CODE_ACCESS
#define READ_ACCESS_TYPE 2
#define ADDR_READ addr_code
#else
#define READ_ACCESS_TYPE 0
#define ADDR_READ addr_read
#endif

static DATA_TYPE glue(glue(slow_ld, SUFFIX), MMUSUFFIX)(target_ulong addr,
                                                        int mmu_idx,
                                                        void *retaddr);
static inline DATA_TYPE glue(io_read, SUFFIX)(target_phys_addr_t physaddr,
                                              target_ulong addr,
                                              void *retaddr)
{
    int state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,state12;
    DATA_TYPE res;
    int index;
     uint64_t ciu_sum0_address; //added by maryyam
   
              //  if ((addr>=0x8001070000000000 && addr<=0x80010700000000B8) || (addr>=0x8001070000000200 && addr<=0x8001070000000370 )){
              //  ciu_sum0_address = 0x100000000;
              // printf("\nio_read:  ciu_sum0_address: %lx\n", ciu_sum0_address);
              // return ciu_sum0_address;
              //  }  
               if(((addr==0x8001070000000000 || addr==0x8001070000000200 )) && (state1==1)){
                ciu_sum0_address = 0x100000000;
              //  if(addr!=0x8001070000000000 && addr!= 0x8001070000000200){
              // printf("addr: %lx\n", addr);
              //  }
               return ciu_sum0_address;
                }
    
                if(((addr==0x8001070000000010 || addr==0x8001070000000220 ))&& (state2==1)){
                ciu_sum0_address = 0x100000000;
               return ciu_sum0_address;
                }
              
               if(((addr==0x8001070000000020 || addr==0x8001070000000240 )) && (state3==1)){
                ciu_sum0_address = 0x100000000;
               return ciu_sum0_address;
                }
    
                if(((addr==0x8001070000000030 || addr==0x8001070000000260 )) && (state4==1)){
                ciu_sum0_address = 0x100000000;
               return ciu_sum0_address;
                }
                
                if(((addr==0x8001070000000040 || addr==0x8001070000000280 )) && (state5==1)){
                ciu_sum0_address = 0x100000000;
               return ciu_sum0_address;
                }
    
                 if(((addr==0x8001070000000050 || addr==0x80010700000002a0 )) && (state6==1)){
                ciu_sum0_address = 0x100000000;
               return ciu_sum0_address;
                }
                
                 if(((addr==0x8001070000000060 || addr==0x80010700000002c0 )) && (state7==1)){
                ciu_sum0_address = 0x100000000;
               return ciu_sum0_address;
                }
    
                 if(((addr==0x8001070000000070 || addr==0x80010700000002e0 )) && (state8==1)){
                ciu_sum0_address = 0x100000000;
               return ciu_sum0_address;
                }
    
                if(((addr==0x8001070000000080 || addr==0x8001070000000300 )) && (state9==1)){
                ciu_sum0_address = 0x100000000;
               return ciu_sum0_address;
                }
                
                if(((addr==0x8001070000000090 || addr==0x8001070000000320 )) && (state10==1)){
                ciu_sum0_address = 0x100000000;
               return ciu_sum0_address;
                }
    
                if(((addr==0x80010700000000a0 || addr==0x8001070000000340 )) && (state11==1)){
                 //   printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^11");
                ciu_sum0_address = 0x100000000;
               return ciu_sum0_address;
                }
                
                if(((addr==0x80010700000000b0 || addr==0x8001070000000360 )) && (state12==1)){
                ciu_sum0_address = 0x100000000;
               // printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^12");
               return ciu_sum0_address;
                }
    index = (physaddr >> IO_MEM_SHIFT) & (IO_MEM_NB_ENTRIES - 1);
    physaddr = (physaddr & TARGET_PAGE_MASK) + addr;
    env->mem_io_pc = (unsigned long)retaddr;
    if (index > (IO_MEM_NOTDIRTY >> IO_MEM_SHIFT)
            && !can_do_io(env)) {
        cpu_io_recompile(env, retaddr);
    }

    env->mem_io_vaddr = addr;

     if( addr == 0xffffffffbbe00cfc)  //reading from pci config space
        {   physaddr= 0xcfc;
            index=10;
			res = io_mem_read[index][2](io_mem_opaque[index], physaddr) ;//>> 16;
			
			return res;
			}

 if(addr >= 0x80011A001fbf0000 && addr <= 0x80011A001fbfffff)
 {
           res = io_mem_read[index][2](io_mem_opaque[index], physaddr) ;//>> 16;

			res = bswap32(res);
			return res;
	}

    if(addr >= UARTLO && addr <= UARTHI)
    {
    	res = io_mem_read[index][0](io_mem_opaque[index], physaddr);
    	return res;
    }

#if SHIFT <= 2
    res = io_mem_read[index][SHIFT](io_mem_opaque[index], physaddr);
#else
#ifdef TARGET_WORDS_BIGENDIAN
    res = (uint64_t)io_mem_read[index][2](io_mem_opaque[index], physaddr) << 32;
    res |= io_mem_read[index][2](io_mem_opaque[index], physaddr + 4);
#else
    res = io_mem_read[index][2](io_mem_opaque[index], physaddr);
    res |= (uint64_t)io_mem_read[index][2](io_mem_opaque[index], physaddr + 4) << 32;
#endif
#endif /* SHIFT > 2 */
    return res;
}

/* handle all cases except unaligned access which span two pages */
DATA_TYPE REGPARM glue(glue(__ld, SUFFIX), MMUSUFFIX)(target_ulong addr,
                                                      int mmu_idx)
{   int mem_offset=0;
    DATA_TYPE res;
    int index;
    target_ulong tlb_addr;
    target_phys_addr_t ioaddr;
    unsigned long addend;
    void *retaddr;
    int hhhh=0;

	if(addr >= 0xffffffffbf000000 && addr <= 0xffffffffbf00003f)
	{
	       hhhh=1;

	}



	 if(addr == 0x8001070000000000)
	{  //If guest wants to access CIU INT0 summary register
	   if(glob_e1000_int == 1){
		   glob_e1000_int=0;
	     return 0x1000000000;  //return that there is a network interrupt
	}
	   else if(glob_uart_int == 1){
		   glob_uart_int=0;
		  return 0x800000000;   //return that there is a uart interrupt
	   }

	}

	  if (addr == 0x8001070000000200)
	  { //If guest wants to access CIU INT0 enable register

	     return 0x88006F1800000000;
	     }



	
	
	

    if(addr >= 0x8001190000000000 && addr <= 0x8001190FFFFFFFFF)
{
	   mem_offset=addr-0x8001190000000000;
           addr=mem_offset+0x8000000010000000;


	}

   if(addr >= 0x80011A0000000000 && addr <= 0x80011A0FFFFFFFFF)
{  ayaz=1;
	}
	   if(addr >= 0x80011B0000000000 && addr <= 0x80011E0FFFFFFFFF)
{
	mem_offset=addr-0x8001190000000000;
           addr=mem_offset+0x8000000010000000;
           //0xffffffffc0000000;

	}
//Following code and similar code in __st, io_read and io_write 
//is written by Ayaz Akram
switch(addr){

   case 0x8001180000000800: 
   case 0x8001180000000C00:    addr=0xffffffffb80003f8;  //RBR
			       break;

    case 0x8001180000000808: 
    case 0x8001180000000C08:   addr=0xffffffffb80003f9;   //IER
                               break;

    case 0x8001180000000810: 
    case 0x8001180000000C10:  addr=0xffffffffb80003fA;   //IIR
                              break;

     case 0x8001180000000818: 
     case 0x8001180000000C18:  addr=0xffffffffb80003fB;    //LCR
                               break;

     case 0x8001180000000820: 
     case 0x8001180000000C20:  addr=0xffffffffb80003fC;        //MCR
                               break;

     case 0x8001180000000828: 
     case 0x8001180000000C28:  addr=0xffffffffb80003fD;      //LSR
                               break;

     case 0x8001180000000830: 
     case 0x8001180000000C30: addr=0xffffffffb80003fE;       //MSR
                              break;

     case 0x8001180000000838: 
     case 0x8001180000000C38: addr=0xffffffffb80003ff;      //SCR
                              break;

     case 0x8001180000000840: 
     case 0x8001180000000C40:  addr=0xffffffffb80003f8;      //THR
			       break;

     case 0x8001180000000850: 
     case 0x8001180000000C50:  addr=0xffffffffb80003fA;      //FCR
                               break;

     case 0x8001180000000880: 
     case 0x8001180000000C80: addr=0xffffffffb80003f8;       //DLL
                              break;

    case 0x8001180000000888:  
    case 0x8001180000000C88: addr=0xffffffffb80003f9;     //DLH
                             break;

    default:		     break;
}

    /* test if there is match for unaligned or IO access */
    /* XXX: could done more in memory macro in a non portable way */
    index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
 redo:
    tlb_addr = env->tlb_table[mmu_idx][index].ADDR_READ;
    if ((addr & TARGET_PAGE_MASK) == (tlb_addr & (TARGET_PAGE_MASK | TLB_INVALID_MASK)) ||  (addr >= 0xfffffffffebc0000 && addr <= 0xfffffffffebdffff)) {
        if (tlb_addr & ~TARGET_PAGE_MASK) {
            /* IO access */
             if(addr >= 0xfffffffffebc0000 && addr <= 0xfffffffffebdffff)
            // if(addr >= 0x80011A0000000000 && addr <= 0x80011A0FFFFFFFFF)
{
         //s printf("\n E1000 :IO: add=%llx \n",addr);
	}
            if (((addr & (DATA_SIZE - 1)) != 0) && addr!=0xffffffffb80003fD && addr!=0xffffffffb80003f9 && addr!=0xffffffffb80003fA
                    && addr!=0xffffffffb80003fB && addr!=0xffffffffb80003fC  &&  addr!=0xffffffffb80003fE  && addr!=0xffffffffb80003ff && !(addr >= 0xfffffffffebc0000 && addr <= 0xfffffffffebdffff))
                goto do_unaligned_access;
            retaddr = GETPC();
            if(addr >= 0xfffffffffebc0000 && addr <= 0xfffffffffebdffff)
            printf("\n E1000 2 :IO: add=%llx \n",addr);
            ioaddr = env->iotlb[mmu_idx][index];
            res = glue(io_read, SUFFIX)(ioaddr, addr, retaddr);
        } else if (((addr & ~TARGET_PAGE_MASK) + DATA_SIZE - 1) >= TARGET_PAGE_SIZE) {
            /* slow unaligned access (it spans two pages or IO) */
        do_unaligned_access:
            retaddr = GETPC();
#ifdef ALIGNED_ONLY
            do_unaligned_access(addr, READ_ACCESS_TYPE, mmu_idx, retaddr);
#endif
            res = glue(glue(slow_ld, SUFFIX), MMUSUFFIX)(addr,
                                                         mmu_idx, retaddr);
        } else {
            /* unaligned/aligned access in the same page */
#ifdef ALIGNED_ONLY
            if ((addr & (DATA_SIZE - 1)) != 0) {
                retaddr = GETPC();
                do_unaligned_access(addr, READ_ACCESS_TYPE, mmu_idx, retaddr);
            }
#endif
            addend = env->tlb_table[mmu_idx][index].addend;
            res = glue(glue(ld, USUFFIX), _raw)((uint8_t *)(long)(addr+addend));
        }
    } else {
        /* the page is not in the TLB : fill it */
        retaddr = GETPC();
#ifdef ALIGNED_ONLY
        if ((addr & (DATA_SIZE - 1)) != 0)
            do_unaligned_access(addr, READ_ACCESS_TYPE, mmu_idx, retaddr);
#endif
        tlb_fill(env, addr, READ_ACCESS_TYPE, mmu_idx, retaddr);
        goto redo;
    }
    return res;
}

/* handle all unaligned cases */
static DATA_TYPE glue(glue(slow_ld, SUFFIX), MMUSUFFIX)(target_ulong addr,
                                                        int mmu_idx,
                                                        void *retaddr)
{
    DATA_TYPE res, res1, res2;
    int index, shift;
    target_phys_addr_t ioaddr;
    unsigned long addend;
    target_ulong tlb_addr, addr1, addr2;

    index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
 redo:
    tlb_addr = env->tlb_table[mmu_idx][index].ADDR_READ;
    if ((addr & TARGET_PAGE_MASK) == (tlb_addr & (TARGET_PAGE_MASK | TLB_INVALID_MASK))) {
        if (tlb_addr & ~TARGET_PAGE_MASK) {
            /* IO access */
            if ((addr & (DATA_SIZE - 1)) != 0)
                goto do_unaligned_access;
            ioaddr = env->iotlb[mmu_idx][index];
            res = glue(io_read, SUFFIX)(ioaddr, addr, retaddr);
        } else if (((addr & ~TARGET_PAGE_MASK) + DATA_SIZE - 1) >= TARGET_PAGE_SIZE) {
        do_unaligned_access:
            /* slow unaligned access (it spans two pages) */
            addr1 = addr & ~(DATA_SIZE - 1);
            addr2 = addr1 + DATA_SIZE;
            res1 = glue(glue(slow_ld, SUFFIX), MMUSUFFIX)(addr1,
                                                          mmu_idx, retaddr);
            res2 = glue(glue(slow_ld, SUFFIX), MMUSUFFIX)(addr2,
                                                          mmu_idx, retaddr);
            shift = (addr & (DATA_SIZE - 1)) * 8;
#ifdef TARGET_WORDS_BIGENDIAN
            res = (res1 << shift) | (res2 >> ((DATA_SIZE * 8) - shift));
#else
            res = (res1 >> shift) | (res2 << ((DATA_SIZE * 8) - shift));
#endif
            res = (DATA_TYPE)res;
        } else {
            /* unaligned/aligned access in the same page */
            addend = env->tlb_table[mmu_idx][index].addend;
            res = glue(glue(ld, USUFFIX), _raw)((uint8_t *)(long)(addr+addend));
        }
    } else {
        /* the page is not in the TLB : fill it */
        tlb_fill(env, addr, READ_ACCESS_TYPE, mmu_idx, retaddr);
        goto redo;
    }
    return res;
}

#ifndef SOFTMMU_CODE_ACCESS

static void glue(glue(slow_st, SUFFIX), MMUSUFFIX)(target_ulong addr,
                                                   DATA_TYPE val,
                                                   int mmu_idx,
                                                   void *retaddr);

static inline void glue(io_write, SUFFIX)(target_phys_addr_t physaddr,
                                          DATA_TYPE val,
                                          target_ulong addr,
                                          void *retaddr)
{
    int index;
    uint64_t ciu_sum0_address;
    int state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,state12;
   // qemu_irq irq;
  // CPUMIPSState * mips; 
   //PITChannelState *s;
  //  int n = 2;
//   SerialState *s;
 //  s->irq->n = 2;
    /*Added by Maryyam to support smp interrupts, IPI*/
     if (addr >= 0x8001070000000600 && addr <= 0x8001070000000658)
    {
        switch(addr){
            case 0x8001070000000600:
                // printf("\n*******cause0: %lx, Cause1: %lx phy_addr: %lx index: %lx*********1\n",envArray[0]->CP0_Cause, envArray[1]->CP0_Cause, physaddr, index);
                         state1=0;
                        envArray[0]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                        //cpu_interrupt(envArray[0], CPU_INTERRUPT_HARD);
                        state1=1;
                   /*  if (envArray[0]->CP0_Cause & CP0Ca_IP_mask) {
                         printf("\nWaaooooo ITS HACK :D Cause %lx \n",envArray[0]->CP0_Cause);
                          printf("\n*******cause0: %lx, Cause1: %lx*********\n", envArray[0]->CP0_Cause, envArray[1]->CP0_Cause);
                         cpu_interrupt(envArray[0], CPU_INTERRUPT_HARD);
                         printf("\nWaaooooo I am back from cpu_interrupt Cause %lx \n", envArray[0]->CP0_Cause);
                     } else {
                         cpu_reset_interrupt(envArray[0], CPU_INTERRUPT_HARD);
                             } */
             break;
             
            case 0x8001070000000608:
                      //   printf("\n*******cause0: %lx, Cause1: %lx*********2\n",envArray[1]->CP0_Cause, envArray[1]->CP0_Cause);
                        state2=0;
                         envArray[1]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                         //cpu_interrupt(envArray[1], CPU_INTERRUPT_HARD);
                         state2=1;
                         
 
             break;
                   
            case 0x8001070000000610:
                        state3=0;
                        envArray[2]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                        ///cpu_interrupt(envArray[2], CPU_INTERRUPT_HARD);
                      //  printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^1");
                        state3=1;
                
            break;
            
            case 0x8001070000000618:
                        state4=0;
                        envArray[3]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                         //cpu_interrupt(envArray[3], CPU_INTERRUPT_HARD);
                        state4=1;
                       // printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^2");
            break;
            
            case 0x8001070000000620:
                        state5=0;
                         envArray[4]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                         //cpu_interrupt(envArray[4], CPU_INTERRUPT_HARD);
                         state5=1;
             break;
             
             case 0x8001070000000628:
                        state6=0;
                         envArray[5]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                         //cpu_interrupt(envArray[5], CPU_INTERRUPT_HARD);
                         state6=1;
             break;
             
             case 0x8001070000000630:
                        state7=0;
                         envArray[6]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                       // cpu_interrupt(envArray[6], CPU_INTERRUPT_HARD);
                         state7=1;
             break;
             
             case 0x8001070000000638:
                        state8=0;
                         envArray[7]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                         //cpu_interrupt(envArray[7], CPU_INTERRUPT_HARD);
                         state8=1;
             break;
             
             case 0x8001070000000640:
                        state9=0;
                         envArray[8]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                        // cpu_interrupt(envArray[8], CPU_INTERRUPT_HARD);
                         state9=1;
             break;
             
             case 0x8001070000000648:
                        state10=0;
                         envArray[9]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                         //cpu_interrupt(envArray[9], CPU_INTERRUPT_HARD);
                         state10=1;
             break;
             
             case 0x8001070000000650:
                        state11=0;
                      //  printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^1");
                         envArray[10]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                         //cpu_interrupt(envArray[10], CPU_INTERRUPT_HARD);
                         state11=1;
             break;
             
             case 0x8001070000000658:
                        state12=0;
                      //  printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^2");
                         envArray[11]->CP0_Cause |= 1 << (2 + CP0Ca_IP);
                          //cpu_interrupt(envArray[11], CPU_INTERRUPT_HARD);
                         state12=1;
             break;
        }
    }
    
    index = (physaddr >> IO_MEM_SHIFT) & (IO_MEM_NB_ENTRIES - 1);
    physaddr = (physaddr & TARGET_PAGE_MASK) + addr;
    if (index > (IO_MEM_NOTDIRTY >> IO_MEM_SHIFT)
            && !can_do_io(env)) {
        cpu_io_recompile(env, retaddr);
    }

    env->mem_io_vaddr = addr;
    env->mem_io_pc = (unsigned long)retaddr;
     if(addr == 0xffffffffbbe00cf8)
     { index=10;
        physaddr=0xcf8;
        io_mem_write[index][2](io_mem_opaque[index],physaddr,val);
		 return;
		 }
	 if( addr == 0xffffffffbbe00cfc)
	 {  index=10;
	 physaddr=0xcfc;
	 io_mem_write[index][2](io_mem_opaque[index],physaddr,val);
	 return;
		 }	//if(addr >= 0xfffffffffebc0000 && addr <= 0xfffffffffebdffff)	 
		  //if(addr >=0x9000000000004000 && addr <=0x900000000FFFFFFF)
		  if(addr >= 0x80011A001fbf0000 && addr <= 0x80011A001fbfffff)
		   {    //printf("\n ST:E1000:addr:0x%llx \n",addr);
		    ayaz2=1;
		  val=bswap32(val);
		  // val=val | 0x1c0;
		  // val=val & 0x00000fff;
			  io_mem_write[index][2](io_mem_opaque[index],physaddr,val);
	          return;
			  }
		 
		 
    if(addr >= UARTLO && addr <= UARTHI)
    {
    	io_mem_write[index][0](io_mem_opaque[index], physaddr, val);
    	return;
    }

#if SHIFT <= 2
    io_mem_write[index][SHIFT](io_mem_opaque[index], physaddr, val);
#else
#ifdef TARGET_WORDS_BIGENDIAN
    io_mem_write[index][2](io_mem_opaque[index], physaddr, val >> 32);
    io_mem_write[index][2](io_mem_opaque[index], physaddr + 4, val);
#else
    io_mem_write[index][2](io_mem_opaque[index], physaddr, val);
    io_mem_write[index][2](io_mem_opaque[index], physaddr + 4, val >> 32);
#endif
#endif /* SHIFT > 2 */
}

void REGPARM glue(glue(__st, SUFFIX), MMUSUFFIX)(target_ulong addr,
                                                 DATA_TYPE val,
                                                 int mmu_idx)
{   int mem_offset=0;
    target_phys_addr_t ioaddr;
    unsigned long addend;
    target_ulong tlb_addr;
    void *retaddr;
    int index;
    int i;
   int casual;  
   	if(addr >= 0xfffffffffebc0000 && addr <= 0xfffffffffebdffff)
	//printf("\n ****E1000:ST: addr : 0x%llx \n",addr);
    //if(addr==0x8001180000000c00){
		
		//printf("this is the address");
		//}
    
//following hack was put in by Nouman so that user mode 
//terminals work.  Now we don't need this code
/*
 if(addr==0x8001180000000c00)
    {
    fprintf(stderr,"%c",(char)val);
    }
*/
//if(addr >=0x80011A00bf000000 && addr <=0x80011A00bf00003f)
	//{ addr |= 0xffffffff00000000; 
		//}

if(addr >= 0xffffffffbf000000 && addr <= 0xffffffffbf00003f)
	{   //addr &= 0x00000000ffffffff;
		printf("\n ****E1000:ST: addr : 0x%llx and val=0x%llx \n",addr,val);
	}
   if(addr == 0xffffffffbbe00cf8)
   {//printf("\n STORE: addr:0x%llx: val:0x%llx \n", addr,val);
   val = val | 0x0000000080000000;  //value to be written in pci configuration space is manipulated according to Malta Mips
    
}




	

switch(addr){

   case 0x8001180000000800: 
   case 0x8001180000000C00:    addr=0xffffffffb80003f8;  //RBR
			       break;

    case 0x8001180000000808: 
    case 0x8001180000000C08:   addr=0xffffffffb80003f9;   //IER
                               break;

    case 0x8001180000000810: 
    case 0x8001180000000C10:  addr=0xffffffffb80003fA;   //IIR
                              break;

     case 0x8001180000000818: 
     case 0x8001180000000C18:  addr=0xffffffffb80003fB;    //LCR
                               break;

     case 0x8001180000000820: 
     case 0x8001180000000C20:  addr=0xffffffffb80003fC;        //MCR
                               break;

     case 0x8001180000000828: 
     case 0x8001180000000C28:  addr=0xffffffffb80003fD;      //LSR
                               break;

     case 0x8001180000000830: 
     case 0x8001180000000C30: addr=0xffffffffb80003fE;       //MSR
                              break;

     case 0x8001180000000838: 
     case 0x8001180000000C38: addr=0xffffffffb80003ff;      //SCR
                              break;

     case 0x8001180000000840: 
     case 0x8001180000000C40:  addr=0xffffffffb80003f8;      //THR
			       break;

     case 0x8001180000000850: 
     case 0x8001180000000C50:  addr=0xffffffffb80003fA;      //FCR
                               break;

     case 0x8001180000000880: 
     case 0x8001180000000C80: addr=0xffffffffb80003f8;       //DLL
                              break;

    case 0x8001180000000888:  
    case 0x8001180000000C88: addr=0xffffffffb80003f9;     //DLH
                             break;

    default:		     break;
}

    index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
 redo:
    tlb_addr = env->tlb_table[mmu_idx][index].addr_write;
    if ((addr & TARGET_PAGE_MASK) == (tlb_addr & (TARGET_PAGE_MASK | TLB_INVALID_MASK))) {
        if (tlb_addr & ~TARGET_PAGE_MASK) {
            /* IO access */
            if (((addr & (DATA_SIZE - 1)) != 0) && addr!=0xffffffffb80003fD && addr!=0xffffffffb80003f9 && addr!=0xffffffffb80003fA
                    && addr!=0xffffffffb80003fB && addr!=0xffffffffb80003fC  &&  addr!=0xffffffffb80003fE  && addr!=0xffffffffb80003ff)
                goto do_unaligned_access;
            retaddr = GETPC();
            ioaddr = env->iotlb[mmu_idx][index];
            glue(io_write, SUFFIX)(ioaddr, val, addr, retaddr);
        } else if (((addr & ~TARGET_PAGE_MASK) + DATA_SIZE - 1) >= TARGET_PAGE_SIZE) {
        do_unaligned_access:
            retaddr = GETPC();
#ifdef ALIGNED_ONLY
            do_unaligned_access(addr, 1, mmu_idx, retaddr);
#endif
            glue(glue(slow_st, SUFFIX), MMUSUFFIX)(addr, val,
                                                   mmu_idx, retaddr);
        } else {
            /* aligned/unaligned access in the same page */
#ifdef ALIGNED_ONLY
            if ((addr & (DATA_SIZE - 1)) != 0) {
                retaddr = GETPC();
                do_unaligned_access(addr, 1, mmu_idx, retaddr);
            }
#endif
            addend = env->tlb_table[mmu_idx][index].addend;
            glue(glue(st, SUFFIX), _raw)((uint8_t *)(long)(addr+addend), val);
        }
    } else {
        /* the page is not in the TLB : fill it */
        retaddr = GETPC();
#ifdef ALIGNED_ONLY
        if ((addr & (DATA_SIZE - 1)) != 0)
            do_unaligned_access(addr, 1, mmu_idx, retaddr);
#endif
        tlb_fill(env, addr, 1, mmu_idx, retaddr);
        goto redo;
    }
}

/* handles all unaligned cases */
static void glue(glue(slow_st, SUFFIX), MMUSUFFIX)(target_ulong addr,
                                                   DATA_TYPE val,
                                                   int mmu_idx,
                                                   void *retaddr)
{
    target_phys_addr_t ioaddr;
    unsigned long addend;
    target_ulong tlb_addr;
    int index, i;

    index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
 redo:
    tlb_addr = env->tlb_table[mmu_idx][index].addr_write;
    if ((addr & TARGET_PAGE_MASK) == (tlb_addr & (TARGET_PAGE_MASK | TLB_INVALID_MASK))) {
        if (tlb_addr & ~TARGET_PAGE_MASK) {
            /* IO access */
            if ((addr & (DATA_SIZE - 1)) != 0)
                goto do_unaligned_access;
            ioaddr = env->iotlb[mmu_idx][index];
            glue(io_write, SUFFIX)(ioaddr, val, addr, retaddr);
        } else if (((addr & ~TARGET_PAGE_MASK) + DATA_SIZE - 1) >= TARGET_PAGE_SIZE) {
        do_unaligned_access:
            /* XXX: not efficient, but simple */
            /* Note: relies on the fact that tlb_fill() does not remove the
             * previous page from the TLB cache.  */
            for(i = DATA_SIZE - 1; i >= 0; i--) {
#ifdef TARGET_WORDS_BIGENDIAN
                glue(slow_stb, MMUSUFFIX)(addr + i, val >> (((DATA_SIZE - 1) * 8) - (i * 8)),
                                          mmu_idx, retaddr);
#else
                glue(slow_stb, MMUSUFFIX)(addr + i, val >> (i * 8),
                                          mmu_idx, retaddr);
#endif
            }
        } else {
            /* aligned/unaligned access in the same page */
            addend = env->tlb_table[mmu_idx][index].addend;
            glue(glue(st, SUFFIX), _raw)((uint8_t *)(long)(addr+addend), val);
        }
    } else {
        /* the page is not in the TLB : fill it */
        tlb_fill(env, addr, 1, mmu_idx, retaddr);
        goto redo;
    }
}

#endif /* !defined(SOFTMMU_CODE_ACCESS) */

#undef READ_ACCESS_TYPE
#undef SHIFT
#undef DATA_TYPE
#undef SUFFIX
#undef USUFFIX
#undef DATA_SIZE
#undef ADDR_READ

