cc=gcc -I ../include 
SUBDIRS=f1 f2 main obj
OBJS=f1.o f2.o main.o
BIN=myapp
OBJS_DIR=obj
BIN_DIR=bin
export cc SUBDIRS OBJS BIN OBJS_DIR BIN_DIR

all:CHECK_DIR $(SUBDIRS)
CHECK_DIR:
	mkdir -p $(BIN_DIR)
$(SUBDIRS):ECHO
	make -C $@	
ECHO:
	@echo $(SUBDIRS)
	@echo begin compile
.PHONY:clean
clean:
	@$(RM) $(OBJS_DIR)/*.o
	@rm -rf $(BIN_DIR)

