/*********************************************************************************
*  Copyright (c) 2010-2011, Elliott Cooper-Balis
*                             Paul Rosenfeld
*                             Bruce Jacob
*                             University of Maryland 
*                             dramninjas [at] gmail [dot] com
*  All rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*  
*     * Redistributions of source code must retain the above copyright notice,
*        this list of conditions and the following disclaimer.
*  
*     * Redistributions in binary form must reproduce the above copyright notice,
*        this list of conditions and the following disclaimer in the documentation
*        and/or other materials provided with the distribution.
*  
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
*  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*********************************************************************************/

#include <stdio.h>
#include "dramsim_test.h"

using namespace DRAMSim;

/* callback functors */
void some_object::read_complete(unsigned id, uint64_t address, uint64_t clock_cycle)
{
	printf("[Callback] read complete: %d 0x%lx cycle=%lu\n", id, address, clock_cycle);
}

void some_object::read_quant_complete(unsigned id, uint64_t address, uint64_t clock_cycle)
{
	printf("[Callback] read_quant complete: %d 0x%lx cycle=%lu\n", id, address, clock_cycle);
}

void some_object::write_complete(unsigned id, uint64_t address, uint64_t clock_cycle)
{
	printf("[Callback] write complete: %d 0x%lx cycle=%lu\n", id, address, clock_cycle);
}

void some_object::write_update_complete(unsigned id, uint64_t address, uint64_t clock_cycle)
{
	printf("[Callback] write_update complete: %d 0x%lx cycle=%lu\n", id, address, clock_cycle);
}

/* FIXME: this may be broken, currently */
void power_callback(double a, double b, double c, double d)
{
	//	printf("power callback: %0.3f, %0.3f, %0.3f, %0.3f\n",a,b,c,d);
}

int some_object::read_test(MultiChannelMemorySystem *mem, uint64_t addr)
{

	for(unsigned i=0; i < 5; i++)
	{
		/* create a transaction and add it */
		// TransactionType type = DATA_QUANT_READ;
		TransactionType type = DATA_READ;
		Transaction *trans = new Transaction(type, addr+0x100UL*(i+1), NULL);
		mem->addTransaction(trans);

		// send a read to channel 1 on the same cycle
		// addr = 1LL<<33 | addr;
		// mem->addTransaction(isWrite, addr);

		for (int j = 0; j < 1; j++)
		{
			mem->update();
		}
	}
	for (int j = 0; j < 200; j++)
	{
		mem->update();
	}
	/* get a nice summary of this epoch */
	mem->printStats(true);

	return 0;
}

int some_object::read_mix_test(MultiChannelMemorySystem *mem, uint64_t addr)
{

	for(unsigned i=0; i < 50; i++)
	{
		/* create a transaction and add it */
		TransactionType type;
		if (i%2 == 0)
		{
			type = DATA_READ;
		}
		else
		{
			type = DATA_QUANT_READ;
		}
		
		Transaction *trans = new Transaction(type, addr+0x100UL*(i), NULL);
		mem->addTransaction(trans);

		// send a read to channel 1 on the same cycle
		// addr = 1LL<<33 | addr;
		// mem->addTransaction(isWrite, addr);

		for (int j = 0; j < 10; j++)
		{
			mem->update();
		}
	}

	for (int j = 0; j < 1000; j++)
	{
		mem->update();
	}
	/* get a nice summary of this epoch */
	mem->printStats(true);

	return 0;
}

int some_object::write_test(MultiChannelMemorySystem *mem, uint64_t addr)
{

	for(unsigned i=0; i < 8; i++)
	{
		/* create a transaction and add it */
		// TransactionType type = DATA_QUANT_READ;
		TransactionType type = DATA_WRITE;
	    int* data = new int(3);	
		Transaction *trans = new Transaction(type, addr+0x040UL*(i), data);
		mem->addTransaction(trans);

		// send a read to channel 1 on the same cycle
		// addr = 1LL<<33 | addr;
		// mem->addTransaction(isWrite, addr);

		for (int j = 0; j < 1; j++)
		{
			mem->update();
		}
	}
	for (int j = 0; j < 200; j++)
	{
		mem->update();
	}
	/* get a nice summary of this epoch */
	mem->printStats(true);

	return 0;
}

int some_object::read_quant_test(MultiChannelMemorySystem *mem, uint64_t addr)
{

	for(unsigned i=0; i < 2; i++)
	{
		/* create a transaction and add it */
		// TransactionType type = DATA_QUANT_READ;
		TransactionType type = DATA_QUANT_READ;
		Transaction *trans = new Transaction(type, addr+0x100UL*(i), NULL);
		mem->addTransaction(trans);

		// send a read to channel 1 on the same cycle
		// addr = 1LL<<33 | addr;
		// mem->addTransaction(isWrite, addr);

		for (int j = 0; j < 1; j++)
		{
			mem->update();
		}
	}
	for (int j = 0; j < 100; j++)
	{
		mem->update();
	}
	/* get a nice summary of this epoch */
	mem->printStats(true);

	return 0;
}


int some_object::update_test(MultiChannelMemorySystem *mem, uint64_t addr, uint64_t addr2)
{

	for(unsigned i=0; i < 8; i++)
	{
		/* create a transaction and add it */
		// TransactionType type = DATA_QUANT_READ;
		TransactionType type = DATA_UPDATE;
		uint64_t addr_ = addr+0x040UL*(i);
		uint64_t addr2_ = addr2+0x040UL*(i);
		Transaction *trans = new Transaction(type, addr_, addr2_, NULL);
		mem->addTransaction(trans);

		for (int j = 0; j < 1; j++)
		{
			mem->update();
		}
	}
	for (int j = 0; j < 100; j++)
	{
		mem->update();
	}
	/* get a nice summary of this epoch */
	mem->printStats(true);

	return 0;
}

int main()
{
	some_object obj;
	TransactionCompleteCB *read_cb = new Callback<some_object, void, unsigned, uint64_t, uint64_t>(&obj, &some_object::read_complete);
	TransactionCompleteCB *write_cb = new Callback<some_object, void, unsigned, uint64_t, uint64_t>(&obj, &some_object::write_complete);
	TransactionCompleteCB *read_quant_cb = new Callback<some_object, void, unsigned, uint64_t, uint64_t>(&obj, &some_object::read_quant_complete);
	TransactionCompleteCB *write_update_cb = new Callback<some_object, void, unsigned, uint64_t, uint64_t>(&obj, &some_object::write_update_complete);

	/* pick a DRAM part to simulate */
	MultiChannelMemorySystem *mem = getMemorySystemInstance("ini/DDR3_micron_32M_8B_x4_sg125.ini", "system.ini", "..", "example_app", 16384);
	mem->RegisterCallbacks(read_cb, write_cb, read_quant_cb, write_update_cb, power_callback);

	printf("dramsim_test main()\n");
	printf("-----MEM1------\n");
	// obj.write_test(mem, 0x100000UL);
	// obj.read_quant_test(mem, 0x100000UL);
	obj.update_test(mem, 0x100000UL, 0x300000UL);
	// obj.read_mix_test(mem, 0x000000UL);

	for (int j = 0; j < 500; j++)
	{
		mem->update();
	}

	return 0;
}
