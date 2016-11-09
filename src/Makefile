#
# OMNeT++/OMNEST Makefile for ks
#
# This file was generated with the command:
#  opp_makemake -f --deep -I../../inet/src -I../../inet/src/inet/common -I../../inet/src/inet/networklayer/common -L../../inet/out/$$\(CONFIGNAME\)/src -lINET -KINET_PROJ=../../inet
#

# Name of target to be created (-o option)
TARGET = ks$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../inet/src \
    -I../../inet/src/inet/common \
    -I../../inet/src/inet/networklayer/common \
    -I. \
    -Iapplication \
    -Iapplication/direct \
    -Iapplication/http \
    -Iapplication/http/client \
    -Iapplication/http/common \
    -Iapplication/http/server \
    -Iapplication/tcp

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../inet/out/$(CONFIGNAME)/src  -lINET
LIBS += -Wl,-rpath,`abspath ../../inet/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/application/direct/HttpDirectClient.o \
    $O/application/direct/HttpDirectServer.o \
    $O/application/http/client/httpClient.o \
    $O/application/http/common/httpCommon.o \
    $O/application/http/server/httpServer.o \
    $O/application/tcp/TCPSocket.o \
    $O/application/tcp/HttpTcpServerApp.o \
    $O/application/tcp/HttpTcpClientApp.o

# Message files
MSGFILES =

# Other makefile variables (-K)
INET_PROJ=../../inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f ks ks.exe libks.so libks.a libks.dll libks.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f application/*_m.cc application/*_m.h
	$(Q)-rm -f application/direct/*_m.cc application/direct/*_m.h
	$(Q)-rm -f application/http/*_m.cc application/http/*_m.h
	$(Q)-rm -f application/http/client/*_m.cc application/http/client/*_m.h
	$(Q)-rm -f application/http/common/*_m.cc application/http/common/*_m.h
	$(Q)-rm -f application/http/server/*_m.cc application/http/server/*_m.h
	$(Q)-rm -f application/tcp/*_m.cc application/tcp/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc application/*.cc application/direct/*.cc application/http/*.cc application/http/client/*.cc application/http/common/*.cc application/http/server/*.cc application/tcp/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/application/direct/HttpDirectClient.o: application/direct/HttpDirectClient.cc \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/features.h \
	application/direct/HttpDirectClient.h \
	application/http/client/httpClient.h \
	application/http/common/httpCommon.h
$O/application/direct/HttpDirectServer.o: application/direct/HttpDirectServer.cc \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/features.h \
	application/direct/HttpDirectServer.h \
	application/http/common/httpCommon.h \
	application/http/server/httpServer.h
$O/application/http/client/httpClient.o: application/http/client/httpClient.cc \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/features.h \
	application/http/client/httpClient.h \
	application/http/common/httpCommon.h
$O/application/http/common/httpCommon.o: application/http/common/httpCommon.cc \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/features.h \
	application/http/common/httpCommon.h
$O/application/http/server/httpServer.o: application/http/server/httpServer.cc \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/features.h \
	application/http/common/httpCommon.h \
	application/http/server/httpServer.h
$O/application/tcp/HttpTcpClientApp.o: application/tcp/HttpTcpClientApp.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/application/tcp/HttpTcpServerApp.o: application/tcp/HttpTcpServerApp.cc \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	application/http/common/httpCommon.h \
	application/http/server/httpServer.h \
	application/tcp/HttpTcpServerApp.h
$O/application/tcp/TCPSocket.o: application/tcp/TCPSocket.cc

