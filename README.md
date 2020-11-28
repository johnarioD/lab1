# Lab_1
Computer Architecture Lab 1

## Answer 1:
After looking through starter_se.py we found the following:  
CPU type can be 'atomic', 'minor', 'hpi', with our command line arguments we chose the 'minor' type  
The clock has a frequency of 1GHz with and receives 3.3 Volts  
The basic units we found to be defined in the file are caches, a memory bus, a cluster of processing units with a number of cores and frequencies that are both defined by our command line arguments (this receives 1.2 Volts)  
Caches include a L1 Instruction cache a L1 Data cache, a L2 and Walk cache, the default cache line size is 64 bytes  
Emulated system memory is 2GB  

## Answer 2:
The files _Config.json_ and _Config.ini_ seem to be two different versions of the same file, both containing info about the emulated hardware & architecture characteristics  

From [_Config.ini_](Stats/starterConfig.ini) we found:  
  
**Clock** = 1000 (assumed MHz) (Line [44](Stats/starterConfig.ini#L44))  
**CPU clock** = 250 (assumed MHz) (Line [58](Stats/starterConfig.ini#L58))  
  
**CPU type**: 'minor' (Line [65](Stats/starterConfig.ini#L65)), round robin policy (Line [124](Stats/starterConfig.ini#L124))  
**Function Units**: 8 units (Line [399](Stats/starterConfig.ini#L399))  
  
**Cache Line Size** = 64 bytes (Line [15](Stats/starterConfig.ini#L15))  
  
**Data Cache**: Size 32KB with 64KB addresses (Lines [187](Stats/starterConfig.ini#L187), [165](Stats/starterConfig.ini#L165)), data/responce/tag latencies 2/1/2 (Lines [170](Stats/starterConfig.ini#L170), [181](Stats/starterConfig.ini#L181), [185](Stats/starterConfig.ini#L185)), 16 write buffers (Line [190](Stats/starterConfig.ini#L190)), clock frequencies: Max = 1THz/, Min=1KHz (Lines [198](Stats/starterConfig.ini#L198), [199](Stats/starterConfig.ini#L199)), block size 64 (Line [213](Stats/starterConfig.ini#L213)), assosiativity type = set associative with associativity 2 (Line [228](Stats/starterConfig.ini#L228), [166](Stats/starterConfig.ini#L166))  
  
**Instruction Cache**: Size 48KB with 64KB addresses (Lines [929](Stats/starterConfig.ini#L929), [911](Stats/starterConfig.ini#L911)), data/responce/tag latencies 1/1/1 (Lines [916](Stats/starterConfig.ini#L916), [927](Stats/starterConfig.ini#L927), [931](Stats/starterConfig.ini#L931)), 8 write buffers (Line [936](Stats/starterConfig.ini#L936)), clock frequencies: Max = 1THz Min = 1KHz (Lines [983](Stats/starterConfig.ini#L983), [984](Stats/starterConfig.ini#L984)), block size 64 (Line [959](Stats/starterConfig.ini#L959)), assosiativity type =  set associative with associativity 3 (Line [974](Stats/starterConfig.ini#L974), [912](Stats/starterConfig.ini#L912))  
  
**L2 cache**: Size 1MB, 64KB addresses (Lines [1235](Stats/starterConfig.ini#L1235), [1217](Stats/starterConfig.ini#L1217)), associativity 16 (Line [1218](Stats/starterConfig.ini#L1218)), data/responce/tag latencies 12/5/12 (Lines [1222](Stats/starterConfig.ini#L1222), [1233](Stats/starterConfig.ini#L1233), [1237](Stats/starterConfig.ini#L1237)), clock frequencies: Max = 1THz Min = 1KHz (Lines [1250](Stats/starterConfig.ini#L1250), [1251](Stats/starterConfig.ini#L1251)), associativity type: base set associative (Line [1262](Stats/starterConfig.ini#L1262)), block size 64 (Line [1265](Stats/starterConfig.ini#L1265))  
  
**Memory**: 2 memories with size 512MB (Lines [1413](Stats/starterConfig.ini#L1413), [1543](Stats/starterConfig.ini#L1543))  
  
From _Stats.txt_ we found:  
  
**Clock Period in ticks**: 1000 system.clk_domain.clock (1 tick is 0.001 ns according to sim_freq, Line: [9](Stats/starterStats.txt#L9))  
  
**No. of _Commited Instructions_**: 5028 (Keyword: system.cpu_cluster.cpus.committedInsts, Line: [14](Stats/starterStats.txt#L14))  
**No. of _Commited Operations_**: 5834 (Keyword: system.cpu_cluster.cpus.committedOps, Line: [15](Stats/starterStats.txt#L15))  
**Overall number of instrcutions/operations**: 5028/5834 (Keywords: sim_insts/sim_ops, Lines: [10](Stats/starterStats.txt#L10),[11](Stats/starterStats.txt#L11))  
  
As it seems, all of our instructions were successfully commited, however, we discovered a discrepancy between the amount of commited operations and instructions. We believe that that is most probably a result of our C compiler utilizing assembly instructions that require more than one operation to finish, possibly some type of macro.  
  
**L2 accesses**: 497 (Keyword: system.cpu_cluster.toL2Bus.snoop_filter.tot_requests, Line: [84](Stats/starterStats.txt#L84))  
If it was not provided, it's sum of L1 misses from data and instruction caches  
(Keywords: system.cpu_cluster.cpus.dcache.overall_misses, system.cpu_cluster.cpus.icache.overall_misses, Lines: [113](Stats/starterStats.txt#113),[314](Stats/starterStats.txt#L314))  

## Answer 3:  
The two main types of in-order CPU architecture used in gem5 are _SimpleCPU_ and _Minor_  

**SimpleCPU**: The SimpleCPU model is a 32 bit RISC, in-order processor model that lacks detail as it utilizes a minimal amount of instructions. It has 32 bit registers, 29 of which are for general use. Reserved registers **_R00_**, **_R01_**, **_R02_** are used for the program counter, stack pointer and flags respectively. Instuctions are always 32 bits and the model has a CPI of 1 with instruction loading pipeline. Instructions and data seem to share the same memory space though instructions always start on address divisible by 4. The gem5 emulated model is broken up in three classes _BaseSimpleCPU_, _AtomicSimpleCPU_, _TimingSimpleCPU_. The first class defines the base architectural stats that are common across the other two models. The _AtomicSimpleCPU_ utilizes the faster _Atomic_ memory acces type while the _TimingSimpleCPU_ utilizes the more detailed _Timing_ memory access type.  

**Minor**: The minor processor model has a fixed pipeline with configurable data structures and execute behaviour. It is intended to be used for processsors with strict "in-order" execution behaviour and can also allow the visualization of an instruction's position in the pipeline with the use of MinorTrace/minorview.py tool. It can be used to simulate the micro-architectural model of a chosen processor with similar capabilities. The model is unable to multithread. It also uses some branch prediction mechanisms to speed up optimize memory access, registry dependencies are managed by a "scoreboard".  

**HPI**: The acronym HPI stands for High-Performance In-order CPU . It is based on the Arm architecture. The HPI CPU timing model is tuned to be representative of a modern in-order Armv8-A implementation. The pipeline of the HPI CPU uses the same four-stage model as the MinorCPU.

(_sources: https://www.gem5.org/documentation/general_docs/cpu_models/SimpleCPU, https://www.simple-cpu.com/cpu-instruction-set-architecture-en.php, https://www.gem5.org/documentation/general_docs/cpu_models/minor_cpu, http://pages.cs.wisc.edu/~swilson/gem5-docs/classMinor_1_1Scoreboard.html_)  

### Simulations:  
We run emulations using "Minor" and "SimpleCPU" architectures on a simple C script that calculates the hypotenuse of a triangle with sides X,Y.  

On our first test we run the simulation on default settings for each CPU architecture.  
Consequently, we run the same code through emulations with clock frequencies of 1GHz, 3GHz, and SimpleMemory, DDR3_1600_8x8 memory models. We found the following results:  
  
| Minor          | Default   |    1GHz    |    3GHz    | SimpleMemory |    DDR3     |
|----------------|-----------|------------|------------|--------------|-------------|
| Ticks          | 44342000  | 50826000   | 39675618   | 33283000     | 42042000    |
| Tickrate       | 468527805 | 573013661  | 402759986  | 331799583    | 425173254   |
| Host time      | 0.09      | 0.09       | 0.10       | 0.10         | 0.10        |
| Commit. Insts. | 12293     | 11685      | 11685      | 11685        | 11685       |
| Commit. Ops.   | 14257     | 13479      | 13479      | 13479        | 13479       |
| L2 access      | 924       | 866        | 861        | 935          | 866         |
  
| Timing         | Default   |    1GHz    |    3GHz    | SimpleMemory |    DDR3     |
|----------------|-----------|------------|------------|--------------|-------------|
| Ticks          | 52221000  | 65665000   |  42160131  |   47810000   |  39945000   |
| Tickrate       | 887928453 | 1774132758 |  768536011 |   1266857438 |  714996338  |
| Host time      | 0.06      | 0.04       |  0.05      |   0.04       |  0.06       |
| Commit. Insts. | 13503     | 11609      |  11609     |   11609      |  11609      |
| Commit. Ops    | 15576     | 13352      |  13352     |   13352      |  13352      |
| L2 access      | 635       | 593        |  593       |   596        |  593        |

Comparing one model to another, it seems that the minor model in general requires less "machine" time to run its programs meaning it should be faster. The simulation for _Minor_, however, takes longer through _gem5_ as the model itself is more complex (as described in the two small paragraphs above). The _SimpleCPU_ with it's "minimal" command set seems to require less instructions and operations to run the same program when compared to the _Minor_ architecture. One obvious difference between the two models is that the _TimingSimpleCPU_ utilizing the "detailed" timing memory access requires far less L2 cache (or higher level memory) accesses compared to _Minor_ regardless of what memory architecture we use.  

**_Comments:_**
Regarding the project, it should be noted that some issues have been detected. For instance, protobuf can only be installed via snap in the latest version of Ubuntu (20.04). In general, the pdf file of the lab exercise contains some commands that simply do not work.The project was simple but not simplistic, since it introduces us smoothly to programs new to us.
