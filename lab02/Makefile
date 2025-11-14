# Makefile for C++ Projects

# 1. 编译器和编译选项
# ==========================================
# 指定C++编译器 (g++ 或 clang++)
CXX = clang++ # <<< CHANGED

# 指定C++编译标志
# -Iinclude: 告诉编译器去 'include' 目录下查找头文件
# -Wall -Wextra: 开启大部分常用的编译警告
# -g: 添加调试信息，方便使用 gdb/lldb 等工具进行调试
# -std=c++17: 指定使用C++17标准 (推荐!)
CXXFLAGS = -Iinclude -Wall -Wextra -g -std=c++17 # <<< CHANGED

# 指定链接标志 (如果需要链接外部库，如 -lpthread)
LDFLAGS =

# 2. 文件和目录定义
# ==========================================
# 最终生成的可执行文件名
TARGET = main

# 源文件目录
SRCDIR = src

# 目标文件 (编译后生成的.o文件) 存放目录
OBJDIR = obj

# 自动查找所有在 src 目录下的 .cpp 源文件
SRCS = $(wildcard $(SRCDIR)/*.cpp) # <<< CHANGED

# 根据源文件列表，自动生成对应的.o文件列表，并指定存放在 obj 目录下
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS)) # <<< CHANGED

# 3. 主要规则 (Targets)
# ==========================================
# 默认目标
.PHONY: all
all: $(TARGET)

# 链接规则：将所有的 .o 文件链接成最终的可执行文件
$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CXX) $(LDFLAGS) -o $@ $^ # <<< CHANGED (使用 CXX, 移除了多余的-g)
	@echo "Build finished: $(TARGET)"

# 编译规则：定义了如何从一个 .cpp 文件编译成一个 .o 文件
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp # <<< CHANGED
	@# 在编译前，确保 obj 目录存在
	@mkdir -p $(OBJDIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c -o $@ $< # <<< CHANGED

# 4. 清理规则
# ==========================================
# .PHONY 声明 'clean' 是一个伪目标
.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJDIR) $(TARGET)

