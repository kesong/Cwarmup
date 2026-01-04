#section 1
#编译相关的内容，包含编译的命令，编译选项，默认路径等
CC						=	cc
CFLAGS				=	-Wall -g -I $(INCLUDE_DIR)

#section 2
#各种目录，源码目录，目标文件生成目录，可执行文件生成目录等
TOP_DIR				:= $(PWD)
SRC_DIR				:= $(TOP_DIR)/src
BUILD_DIR			:= $(TOP_DIR)/build
INCLUDE_DIR		:= $(TOP_DIR)/include
TEST_DIR			:= $(TOP_DIR)/test
LIB_DIR				:= $(TOP_DIR)/lib
SUBDIR				:= src test lib
VPATH					:= src test include lib

#section 3
#打包库函数相关的命令和打包选项，生成相应的库文件
AR						= ar
ARFLAGS				= crs
LIBRARY				= libstack.a libqueue.a
BUILD_LIB			= $(addprefix $(BUILD_DIR)/,$(LIBRARY))

#section 4
#链接相关内容，链接命令，链接选项
LD						=	ld
LDFLAGS				=	-L$(LIB_DIR)

#section 5
export TOP_DIR SRC_DIR BUILD_DIR INCLUDE_DIR TEST_DIR LIB_DIR

#section 6
#所有的源码文件,即.c文件
SRC						=	$(wildcard $(SRC_DIR)/*.c)
MAIN_SRC			=	$(wildcard $(TOP_DIR)/*.c)
TEST_SRCS			=	$(wildcard $(TEST_DIR)/*.c)
LIB_SRCS			=	$(wildcard $(LIB_DIR)/*.c)
SRCS					=	$(SRC) $(TEST_SRCS) $(MAIN_SRC) $(LIB_SRCS)
NO_DIR_SRCS		=	$(notdir $(SRCS))

#section 7
#不同目标生成方式的多种组合,要编译成的目标文件有哪些，一般都会用函数将.c文件转换成.o文件
#object（.o）文件不适合用wildcard函数，因为很多时候.o文件还未生成，用wildcard函数得到的多为空值，在将%.o文件作为target的时候导致不会执行这个target下面的命令
#有的函数的结果会包含文件路径，看是需要获取单纯的文件名还是获取带有文件所在路径的文件名
#组合一，源文件后缀名.c直接替换为.o，此种方法的.o文件带有完整的目录路径
SRC_OBJS			=	$(subst .c,.o,$(SRC))
TEST_OBJS			=	$(subst .c,.o,$(TEST_SRCS))
LIB_OBJS			= $(subst .c,.o,$(LIB_SRCS))
MAIN_OBJ			=	$(subst .c,.o,$(MAIN_SRC))
OBJS					= $(SRC_OBJS) $(TEST_OBJS) $(MAIN_OBJ) $(LIB_OBJS)
BUILD_OBJS		= $(addprefix $(BUILD_DIR)/,$(notdir $(OBJS)))

#section 8
#特殊的.o文件，只获取文件名，然后添加目录前缀，前缀就是希望这个.o文件保存的目录
BUILD_MAIN_OBJ	=	$(addprefix $(BUILD_DIR)/,$(notdir $(MAIN_OBJ)))
BUILD_LIB_OBJS		= $(addprefix $(BUILD_DIR)/,$(notdir $(LIB_OBJS)))

#section 9
#组合二，去掉.c文件的目录名，只获取文件名，然后与存放编译结果的目录bin目录进行组合. $(BIN_DIR)可以去掉，用$(addprefix ,,)函数添加目录名
#SRC_OBJS			=	$(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(wildcard $(SRC))))
#TEST_OBJS		=	$(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(wildcard $(TEST_SRCS))))
#LIB_OBJS			=	$(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(wildcard $(LIB_SRCS))))
#MAIN_OBJS		=	$(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(wildcard $(MAIN_SRCS))))

#section 10
#组合三，更简单的一种获取不带目录前缀的.c文件名的方法，然后将名称中的.c替换成.o，然后再跟目录进行组合
#OBJS					=	$(addprefix $(BUILD_DIR)/,$(notdir $(SRC_OBJS))) $(addprefix $(BUILD_DIR)/,$(notdir $(TEST_OBJS)))
#OBJS					= $(NO_DIR_SRCS:%.c=%.o)
#BUILD_OBJS		= $(addprefix $(BUILD_DIR)/,$(OBJS))
#OBJS					=	$(patsubst %.c,$(BIN_DIR)/%.o,$(notdir $(wildcard $(SRCS))))

#section 11
#更简单的一种将所有SRCS源文件中的.c替换为.o的方式
#OBJS					= $(SRCS:%.c=%.o)

#sectino 12
#可执行文件，一般都是编译整个流程最后的生成文件，也是代码运行的体现
TARGETS=$(BUILD_DIR)/binary_tree_main

#section 13
#调试用，打印变量信息，看变量内容是否正确
$(info $(OBJS))
$(info $(BUILD_OBJS))

#section 14
#终端输入make命令不添加任何目标，默认执行makefile中第一行的目标，本文件中第一行符合make规则写法的目标就是就是all这个目标
all: $(SUBDIR) $(TARGETS) 

#section 15
#	-C参数用来切换目录，切换到对应目录下执行make命令,子目录下没有makefile文件时，不需要切换到子目录执行make命令
$(SUBDIR): RUN
	mkdir -p $(BUILD_DIR)
	#make -C $@

#section 16
# 生成最终的可执行文件
# cc -Wall -g -I /home/apuser/workspace/Cwarmup/c0014_binary_tree/include /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/binary_tree_main.o 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/binary_tree.o /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/print_ADT.o 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/test_player.o /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/queue.o 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/stack.o /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/libstack.a 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/libqueue.a -o /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/binary_tree_main
RUN:
$(TARGETS): $(BUILD_MAIN_OBJ) $(BUILD_OBJS) $(BUILD_LIB)
	$(CC) $(CFLAGS) $^ -o $@


#section 17
#	打包多个库函数，生成静态库，将不同名称的库函数.的o文件分别打包成.a文件
# 执行make，语句展开如下
# for o_file in /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/queue.o /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/stack.o; 
# do ar crs /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/lib$(basename ${o_file%.o}).a $o_file; done
$(BUILD_LIB): $(BUILD_LIB_OBJS)
	$(call archive_o_file,$^)

#section 17
#	打包单个库函数，生成静态库，将库函数.的o文件打包成.a文件，这里是静态库
#$(BUILD_LIB): $(BUILD_LIB_OBJS)
	#$(AR) $(ARFLAGS) $@ $^
	
#section 17
# 打包单个库函数，生成静态库，将库函数.的o文件打包成.a文件，如果这里的依赖对象是$(LIB_OBJS)，在下面的section中没有编写生成$(LIB_OBJS)的语句，
# 会执行makefile的隐含规则，会先自动编译.c文件，在当前目录生成.o文件。
#$(BUILD_LIB): $(LIB_OBJS)
	#$(AR) $(ARFLAGS) $@ $^

#section 18
#	单独编译lib目录下的.c文件，生成.o文件
#$(LIB_OBJS): $(LIB_SRCS)
	#$(CC) $(CFLAGS) -c $< -o $@

#section 19
#	打包库函数，生成动态库，将.o文件打包成.so文件, （本案用不到）
#$(SHARE_OBJ): $(SRCS)
	#$(CC) $(CFLAGS) -fpic

#section 20，.o文件都在build目录
#	将各个目录下生成的.o文件移动到build目录
#$(BUILD_OBJS):
	#find . -name "*.o" -exec mv {} $(BUILD_DIR) \;

#section 21,编译.c文件,使用自定义的函数，逐个编译.c文件。
#	使用这个编译方式，生成.o文件会在build目录，各个子目录下也不需要单独的makefile文件了。
$(BUILD_OBJS): $(SRCS)
	$(call compile_c_file,$(SRCS))


# 调试技巧（Debug）
# 将每个make编译语句前面加上#注释掉，然后在每个命令前面增加一个特殊字符，make执行的时候不会执行该命令，但是会将命令展开，这样就知道不同的命令执行的效果，方便排查和修改
# 如下每个范例通过在编译语句前面增加不同的特殊字符{，@，！等来识别不同语句展开后打印的内容

#section 21，编译.c文件
#依赖文件列表可以为空，直接执行下面的命令就行了，命令列表也是可以为空，那就是空语句
#这种写法生成的.o文件都在makefile所在的目录
#运行make，语句展开如下：
# cc -Wall -g -I /home/apuser/workspace/Cwarmup/c0014_binary_tree/include -c /home/apuser/workspace/Cwarmup/c0014_binary_tree/src/binary_tree.c 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/src/print_ADT.c /home/apuser/workspace/Cwarmup/c0014_binary_tree/test/test_player.c 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/binary_tree_main.c /home/apuser/workspace/Cwarmup/c0014_binary_tree/lib/queue.c 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/lib/stack.c 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/binary_tree_main.o
#$(BUILD_OBJS): $(SRCS)
	#@$(CC) $(CFLAGS) -c $^ $@


#section 21,编译.c文件
#编译生成.o文件，要放到最下方，否则上面section 20会找不到.o文件，
#make的依赖解析是从上至下，执行顺序也是从上至下，这就要求依赖文件的生成必须从下至上，最下面生成最早的依赖，一般就是.o文件
#执行make，语句展开如下：
# *cc -Wall -g -I /home/apuser/workspace/Cwarmup/c0014_binary_tree/include -c /home/apuser/workspace/Cwarmup/c0014_binary_tree/src/binary_tree.c 
# -o /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/binary_tree_main.o
#$(BUILD_MAIN_OBJ): $(MAIN_SRC)
	#*$(CC) $(CFLAGS) -c $< -o $@
	
#section 22,编译.c文件
# error, 这种写法会导致只有$(SRCS)展开后的第一个.c文件作为源文件，目标中每一个.o文件的源文件都是它。
# 可能在生成.o文件这一步没有问题，最后链接的时候，由于多个.o文件都包含同样的代码段，导致链接报错，错误是重复定义某个函数
# 重复定义一般会出现在头文件（.h）的重复包含中，这里的写法也会导致出现重复定义的错误
# 执行make，语句展开如下：
# cc -Wall -g -I /home/apuser/workspace/Cwarmup/c0014_binary_tree/include -c /home/apuser/workspace/Cwarmup/c0014_binary_tree/src/binary_tree.c 
# -o /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/binary_tree_main.o
#$(BUILD_OBJS): $(SRCS)
	#$(CC) $(CFLAGS) -c $< -o $@

#section 23
# error, 这种写法会报错，-c后面指定的是要编译的多个文件名，这个时候不能用-o参数,
# make没有那么智能，他无法将目标里面的多个.o与依赖里面的多个.c形成一一对应,所以就报错了。
# 执行make，语句展开如下：
# cc -Wall -g -I /home/apuser/workspace/Cwarmup/c0014_binary_tree/include -c /home/apuser/workspace/Cwarmup/c0014_binary_tree/src/binary_tree.c 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/src/print_ADT.c /home/apuser/workspace/Cwarmup/c0014_binary_tree/test/test_player.c 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/binary_tree_main.c /home/apuser/workspace/Cwarmup/c0014_binary_tree/lib/queue.c 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/lib/stack.c 
# -o /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/binary_tree_main.o
#$(BUILD_OBJS): $(SRCS)
	#$(CC) $(CFLAGS) -c $^ -o $@

#section 24
# error, 这种写法不会执行编译，没有.o文件生成，因为make也不知道%.o怎么去匹配，去匹配哪些文件
# 依赖文件也必须是已知的,target都必须是已知的值（字符串）否则会导致target下面的命令不会执行
# cc -Wall -g -I /home/apuser/workspace/Cwarmup/c0014_binary_tree/include -c /home/apuser/workspace/Cwarmup/c0014_binary_tree/src/binary_tree.c 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/src/print_ADT.c /home/apuser/workspace/Cwarmup/c0014_binary_tree/test/test_player.c 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/binary_tree_main.c /home/apuser/workspace/Cwarmup/c0014_binary_tree/lib/queue.c 
# /home/apuser/workspace/Cwarmup/c0014_binary_tree/lib/stack.c 
# -o /home/apuser/workspace/Cwarmup/c0014_binary_tree/build/binary_tree_main.o
#$(BUILD_DIR)/%.o: %.c 
	#$(CC) $(CFLAGS) -c $^ -o $@
	
#section 25
#自定义的函数，获取某个文件夹下的所有文件名，自定义函数中包含shell的if或者for语句时，do或者when里面的每条语句最后都得用分号结尾
#自定义函数的函数体为多行时，从第二行（函数名为第一行）开始，结尾要用反斜线，最后两行的结尾不用加反斜线
#shell变量需要使用双美元符号（$$）来取值
#$(get_obj_file_list dir,files)
define get_file_list
	for d in $1; do													\
		echo $$d/*.o > $2; 										\
	done
endef

#$(get_file_list dir,files)
define get_file_list
	for d in $1; do											\
		echo $$d > $2; 										\
	done
endef

#$(delete_file file)
define delete_file
	for fl in $1; do										\
		if [ -f $$fl ]; then 							\
			rm $$fl;												\
		else 															\
			echo "$$fl not exist";					\
		fi																\
	done
endef

#makefile中有多行shell语句（这里用的是for）时候，需要在行结尾加上分号";"，否则会报如下这个错误
# /bin/sh: 1: Syntax error: end of file unexpected (expecting "done")
# $(basename )使用的是makefile函数，不是shell，所以前面需要使用两个$$第一个美元符号是shell的取变量，第二个美元符号是makefile变量和函数的引用方法，
# basename的变量只能是makefile变量的获取方式，由于该语句嵌入在shell语句中，所以也得使用两个$$符号。
# 总结：makefile中编写shell语句，shell命令或者语句获取mafefile定义的变量时，需要对该变量前使用双$符号（$$）。
# $(BUILD_DIR)只使用一个美元符号($)就行了，因为这个值的获取不管是按照shell变量还是makefile的变量来获取都完全一样
#$(compile c file)
define compile_c_file
	for c_file in $1; do										\
		$(CC) $(CFLAGS) -c $$c_file -o $(BUILD_DIR)/$$(basename $${c_file%.c}).o;	\
	done
endef

#依次打包lib目录下的多个库函数的.o文件成.a文件
#$(archive static library)
define archive_o_file
	for o_file in $1; do										\
		$(AR) $(ARFLAGS) $(BUILD_DIR)/lib$$(basename $${o_file%.o}).a $$o_file;	\
	done
endef

#section 26
#clean those files generated during compile
clean:
	rm -rf *.o *.gch core
	$(call delete_file,$(SRC_OBJS))
	$(call delete_file,$(TEST_OBJS))
	$(call delete_file,$(LIB_OBJS))
	$(shell if [ -e $(BUILD_DIR) ]; then rm -rf $(BUILD_DIR); fi)
	
