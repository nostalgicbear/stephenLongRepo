####################################################
# PSP Makefile generated for GNU Make by ProDG VSI #
####################################################

.SILENT:

unexport MAKEFLAGS
unexport MFLAGS

OUTDIR = PSP_DebugOpt
INTDIR = PSP_DebugOpt

LIBS=\
	crt0_prx.o\
	libgu.a\
	libgum.a\
	libkernel.a\
	ctrl_stub.a\
	display_stub.a\
	ge_user_stub.a\
	kernel_bridge.o\

WLIBS=\

AS=pspsnc
AS_FLAGS=\
	-DSN_TARGET_PSP_PRX\
	-D_DEBUG\
	-I$(SCE_PSP_HW_ROOT)/include\
	-I.\
	-c\
	-Xmserrors\
	-g\

CC=pspsnc
CC_FLAGS=\
	-DSN_TARGET_PSP_PRX\
	-D_DEBUG\
	-I$(SCE_PSP_HW_ROOT)/include\
	-I.\
	-c\
	-Xmserrors\
	-MMD\
	-g\
	-O3\
	--use_pch="PSP_DebugOpt/tempprx.pch"\

CXX=pspsnc
CXX_FLAGS=\
	-DSN_TARGET_PSP_PRX\
	-D_DEBUG\
	-I$(SCE_PSP_HW_ROOT)/include\
	-I.\
	-c\
	-Xmserrors\
	-MMD\
	-g\
	-O3\
	--use_pch="PSP_DebugOpt/tempprx.pch"\

LD=pspsnc
LD_FLAGS=\
	-L$(SCE_PSP_HW_ROOT)/lib\
	-Wl,-r -Wl,-dc\
	-g\

OBJS=\
	"PSP_DebugOpt/stdafx.obj"\
	"PSP_DebugOpt/breakout.obj"\
	"PSP_DebugOpt/breakout_glfw.obj"\
	"PSP_DebugOpt/breakout_psp.obj"\

CST_OBJS=\

CST_OUTS=\

CUSTOM: $(CST_OUTS) $(CST_OBJS)

COMPILE: $(OBJS)

ifneq ($(DBS),COMPILE)
"PSP_DebugOpt/stdafx.obj":
else
"PSP_DebugOpt/stdafx.obj":
endif
	@echo ProDG Compiling "c:/Users/user/Desktop/breakPC/PSP PRX1/PSP PRX1/stdafx.cpp"
	$(CXX) -DSN_TARGET_PSP_PRX -D_DEBUG -I$(SCE_PSP_HW_ROOT)/include -I. -c -Xmserrors -MMD -g -O3 --create_pch="PSP_DebugOpt/tempprx.pch" "c:/Users/user/Desktop/breakPC/PSP PRX1/PSP PRX1/stdafx.cpp" -o $@

ifneq ($(DBS),COMPILE)
"PSP_DebugOpt/breakout.obj": "PSP_DebugOpt/stdafx.obj"
else
"PSP_DebugOpt/breakout.obj":
endif
	@echo ProDG Compiling "c:/Users/user/Desktop/breakPC/PSP PRX1/PSP PRX1/breakout.cpp"
	$(CXX) $(CXX_FLAGS) "c:/Users/user/Desktop/breakPC/PSP PRX1/PSP PRX1/breakout.cpp" -o $@

ifneq ($(DBS),COMPILE)
"PSP_DebugOpt/breakout_glfw.obj": "PSP_DebugOpt/stdafx.obj"
else
"PSP_DebugOpt/breakout_glfw.obj":
endif
	@echo ProDG Compiling "c:/Users/user/Desktop/breakPC/PSP PRX1/PSP PRX1/breakout_glfw.cpp"
	$(CXX) $(CXX_FLAGS) "c:/Users/user/Desktop/breakPC/PSP PRX1/PSP PRX1/breakout_glfw.cpp" -o $@

ifneq ($(DBS),COMPILE)
"PSP_DebugOpt/breakout_psp.obj": "PSP_DebugOpt/stdafx.obj"
else
"PSP_DebugOpt/breakout_psp.obj":
endif
	@echo ProDG Compiling "c:/Users/user/Desktop/breakPC/PSP PRX1/PSP PRX1/breakout_psp.cpp"
	$(CXX) $(CXX_FLAGS) "c:/Users/user/Desktop/breakPC/PSP PRX1/PSP PRX1/breakout_psp.cpp" -o $@

LINK: "PSP_DebugOpt/tempprx.obj"

"PSP_DebugOpt/tempprx.obj" : $(CST_OBJS) $(OBJS)
	@echo ProDG Linking $@
	$(LD) $(LD_FLAGS) --start-group $(CST_OBJS) $(OBJS) $(LIBS) --end-group -o $@

