cmake_minimum_required(VERSION 3.10)
project(cpython-portable VERSION 0.1)

#last good version tested
set(PYSRC_LASTGOOD "3.9")

#where are the sources?
if(NOT DEFINED PYSRC)
    message(FATAL_ERROR "Set the location of extracted Python sources using -DPYSRC=<dir>")
endif()
message("Using Python sources in ${PYSRC}")

#what version are the sources?
if(NOT DEFINED PYVER)
    message(FATAL_ERROR "Set the version of extracted Python sources using -DPYVER=<major>.<minor>")
endif()
message("Using Python version in ${PYVER}")

if(NOT ${PYVER} VERSION_EQUAL ${PYSRC_LASTGOOD})
    message(WARNING "Not using the last good version ${PYSRC_LASTGOOD}. Compatibility is not guaranteed")
endif()

include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckStructHasMember)
include(CheckTypeSize)
include(CheckLibraryExists)

find_library(HAVE_LIBUTIL util)
find_library(HAVE_LIBZ z)
find_library(HAVE_LIBREADLINE readline)
find_library(HAVE_LIBFFI ffi)
find_library(HAVE_LIBSQLITE3 sqlite3)

#configure pyconfig.h
option(DOUBLE_IS_LITTLE_ENDIAN_IEEE754 "Define if C doubles are 64-bit IEEE 754 binary format, stored with the least significant byte first" 1)
option(ENABLE_IPV6 "Enable IPv6")
check_function_exists(accept4 HAVE_ACCEPT4)
check_function_exists(acosh HAVE_ACOSH)
list(APPEND CMAKE_EXTRA_INCLUDE_FILES netdb.h)
check_type_size("struct addrinfo" ADDRINFO)
list(POP_BACK CMAKE_EXTRA_INCLUDE_FILES)
check_function_exists(alarm HAVE_ALARM)
option(HAVE_ALIGNED_REQUIRED "Define if aligned memory access is required")
check_include_file(alloca.h HAVE_ALLOCA_H)
check_symbol_exists(altzone "time.h" HAVE_ALTZONE)
check_function_exists(asinh HAVE_ASINH)
check_include_file(asm/types.h HAVE_ASM_TYPES_H)
check_function_exists(atanh HAVE_ATANH)
check_function_exists(bind_textdomain_codeset HAVE_BIND_TEXTDOMAIN_CODESET)
check_include_file(bluetooth/bluetooth.h HAVE_BLUETOOTH_BLUETOOTH_H)
check_include_file(bluetooth.h HAVE_BLUETOOTH_H)

#check_function_exists(chflags HAVE_CHFLAGS)
check_function_exists(chown HAVE_CHOWN)
check_function_exists(chroot HAVE_CHROOT)
check_function_exists(clock HAVE_CLOCK)
check_function_exists(clock_getres HAVE_CLOCK_GETRES)
check_function_exists(clock_gettime HAVE_CLOCK_GETTIME)
check_function_exists(clock_settime HAVE_CLOCK_SETTIME)
set(HAVE_COMPUTED_GOTOS "Define if the C compiler supports computed gotos" 1)
check_function_exists(confstr HAVE_CONFSTR)
check_include_file(conio.h HAVE_CONIO_H)
check_function_exists(copysign HAVE_COPYSIGN)
check_function_exists(copy_file_range HAVE_COPY_FILE_RANGE)
check_include_file(crypt.h HAVE_CRYPT_H)
check_function_exists(crypt_r HAVE_CRYPT_R)
check_function_exists(ctermid HAVE_CTERMID)
check_function_exists(ctermid_r HAVE_CTERMID_R)
check_function_exists(filter HAVE_CURSES_FILTER)
check_include_file(curses.h HAVE_CURSES_H)
check_function_exists(has_key HAVE_CURSES_HAS_KEY)
check_function_exists(immedok HAVE_CURSES_IMMEDOK)
check_symbol_exists(is_pad "curses.h" HAVE_CURSES_IS_PAD)
check_function_exists(is_term_resized HAVE_CURSES_IS_TERM_RESIZED)
check_function_exists(resizeterm HAVE_CURSES_RESIZETERM)
check_function_exists(resize_term HAVE_CURSES_RESIZE_TERM)
check_function_exists(syncok HAVE_CURSES_SYNCOK)
check_function_exists(typeahead HAVE_CURSES_TYPEAHEAD)
check_function_exists(use_env HAVE_CURSES_USE_ENV)
check_function_exists(wchgat HAVE_CURSES_WCHGAT)
check_function_exists(isfinite HAVE_DECL_ISFINITE)
check_function_exists(isinf HAVE_DECL_ISINF)
check_function_exists(isnan HAVE_DECL_ISNAN)
check_symbol_exists(RTLD_DEEPBIND "dlfcn.h" HAVE_DECL_RTLD_DEEPBIND)
check_symbol_exists(RTLD_GLOBAL "dlfcn.h" HAVE_DECL_RTLD_GLOBAL)
check_symbol_exists(RTLD_LAZY "dlfcn.h" HAVE_DECL_RTLD_LAZY)
check_symbol_exists(RTLD_LOCAL "dlfcn.h" HAVE_DECL_RTLD_LOCAL)
check_symbol_exists(RTLD_MEMBER "dlfcn.h" HAVE_DECL_RTLD_MEMBER)
check_symbol_exists(RTLD_NODELETE "dlfcn.h" HAVE_DECL_RTLD_NODELETE)
check_symbol_exists(RTLD_NOLOAD "dlfcn.h" HAVE_DECL_RTLD_NOLOAD)
check_symbol_exists(RTLD_NOW "dlfcn.h" HAVE_DECL_RTLD_NOW)
check_symbol_exists(tzname "time.h" HAVE_DECL_TZNAME)

if(UNIX)
    if(EXISTS "/dev/ptc")
        set(HAVE_DEV_PTC 1)
    endif()
    if(EXISTS "/dev/ptmx")
        set(HAVE_DEV_PTMX 1)
    endif()
endif()
check_include_file(direct.h HAVE_DIRECT_H)
check_symbol_exists(d_type "time.h" HAVE_DECL_TZNAME)
check_struct_has_member("struct dirent" d_type dirent.h HAVE_DIRENT_D_TYPE)
check_include_file(dirent.h HAVE_DIRENT_H)
check_symbol_exists(dirfd "dirent.h" HAVE_DIRFD)
check_include_file(dlfcn.h HAVE_DLFCN_H)
check_function_exists(dlopen HAVE_DLOPEN)
check_function_exists(dup2 HAVE_DUP2)
check_function_exists(dup3 HAVE_DUP3)
check_function_exists(_dyld_shared_cache_contains_path HAVE_DYLD_SHARED_CACHE_CONTAINS_PATH)
option(HAVE_DYNAMIC_LOADING "Defined when any dynamic module loading is enabled" 1)
check_include_file(endian.h HAVE_ENDIAN_H)
check_function_exists(epoll HAVE_EPOLL)
check_function_exists(epoll_create1 HAVE_EPOLL_CREATE1)
check_function_exists(erf HAVE_ERF)
check_function_exists(erfc HAVE_ERFC)
check_include_file(errno.h HAVE_ERRNO_H)
check_function_exists(execv HAVE_EXECV)
check_function_exists(explicit_bzero HAVE_EXPLICIT_BZERO)
check_function_exists(explicit_memset HAVE_EXPLICIT_MEMSET)
check_function_exists(expm1 HAVE_EXPM1)
check_function_exists(faccessat HAVE_FACCESSAT)
check_function_exists(fchdir HAVE_FCHDIR)
check_function_exists(fchmod HAVE_FCHMOD)
check_function_exists(fchmodat HAVE_FCHMODAT)
check_function_exists(fchown HAVE_FCHOWN)
check_function_exists(fchownat HAVE_FCHOWNAT)
check_include_file(fcntl.h HAVE_FCNTL_H)
check_function_exists(fdatasync HAVE_FDATASYNC)
check_function_exists(fdopendir HAVE_FDOPENDIR)
check_function_exists(fdwalk HAVE_FDWALK)
check_function_exists(fexecve HAVE_FEXECVE)
check_function_exists(finite HAVE_FINITE)
check_function_exists(flock HAVE_FLOCK)
check_function_exists(fork HAVE_FORK)
check_function_exists(forkpty HAVE_FORKPTY)
check_function_exists(fpathconf HAVE_FPATHCONF)
check_function_exists(fseek64 HAVE_FSEEK64)
check_function_exists(fseeko HAVE_FSEEKO)
check_function_exists(fstatat HAVE_FSTATAT)
check_function_exists(fstatvfs HAVE_FSTATVFS)
check_function_exists(fsync HAVE_FSYNC)
check_function_exists(ftell64 HAVE_FTELL64)
check_function_exists(ftello HAVE_FTELLO)
check_function_exists(ftime HAVE_FTIME)
check_function_exists(ftruncate HAVE_FTRUNCATE)
check_function_exists(futimens HAVE_FUTIMENS)
check_function_exists(futimes HAVE_FUTIMES)
check_function_exists(futimesat HAVE_FUTIMESAT)
check_function_exists(gai_strerror HAVE_GAI_STRERROR)
check_function_exists(gamma HAVE_GAMMA)
check_function_exists(getaddrinfo HAVE_GETADDRINFO)
option(HAVE_GCC_ASM_FOR_X87 "Define if we can use gcc inline assembler to get and set x87 control word")
check_type_size("__uint128_t" GCC_UINT128_T)
check_function_exists(flockfile HAVE_GETC_UNLOCKED_1)
check_function_exists(getc_unlocked HAVE_GETC_UNLOCKED_2)
check_function_exists(funlockfile HAVE_GETC_UNLOCKED_3)
if(HAVE_GETC_UNLOCKED_1 AND HAVE_GETC_UNLOCKED_2 AND HAVE_GETC_UNLOCKED_3)
    set(HAVE_GETC_UNLOCKED 1)
endif()
check_function_exists(getentropy HAVE_GETENTROPY)
check_function_exists(getgrgid_r HAVE_GETGRGID_R)
check_function_exists(getgrnam_r HAVE_GETGRNAM_R)
check_function_exists(getgrouplist HAVE_GETGROUPLIST)
check_function_exists(getgroups HAVE_GETGROUPS)
check_function_exists(gethostbyname HAVE_GETHOSTBYNAME)
#check_function_exists(gethostbyname_r HAVE_GETHOSTBYNAME_R)
#set(HAVE_GETHOSTBYNAME_R_6_ARG 1)
check_function_exists(getitimer HAVE_GETITIMER)
check_function_exists(getloadavg HAVE_GETLOADAVG)
check_function_exists(getlogin HAVE_GETLOGIN)
check_function_exists(getnameinfo HAVE_GETNAMEINFO)
check_function_exists(getpagesize HAVE_GETPAGESIZE)
check_function_exists(getpeername HAVE_GETPEERNAME)
check_function_exists(getpgid HAVE_GETPGID)
check_function_exists(getpgrp HAVE_GETPGRP)
check_function_exists(getpid HAVE_GETPID)
check_function_exists(getpriority HAVE_GETPRIORITY)
check_function_exists(getpwent HAVE_GETPWENT)
check_function_exists(getpwnam_r HAVE_GETPWNAM_R)
check_function_exists(getpwuid_r HAVE_GETPWUID_R)
check_function_exists(getrandom HAVE_GETRANDOM)
check_symbol_exists(getrandom "sys/random.h" HAVE_GETRANDOM_SYSCALL)
check_function_exists(getresgid HAVE_GETRESGID)
check_function_exists(getresuid HAVE_GETRESUID)
check_function_exists(getsid HAVE_GETSID)
check_function_exists(getspent HAVE_GETSPENT)
check_function_exists(getspnam HAVE_GETSPNAM)
check_function_exists(getwd HAVE_GETWD)

check_include_file(grp.h HAVE_GRP_H)
check_function_exists(hstrerror HAVE_HSTRERROR)
check_function_exists(le64toh HAVE_HTOLE64)
check_function_exists(hypot HAVE_HYPOT)
check_include_file(ieeefp.h HAVE_IEEEFP_H)
check_function_exists(if_nameindex HAVE_IF_NAMEINDEX)
check_function_exists(inet_aton HAVE_INET_ATON)
check_function_exists(inet_pton HAVE_INET_PTON)
check_function_exists(initgroups HAVE_INITGROUPS)
check_include_file(inttypes.h HAVE_INTTYPES_H)
check_include_file(io.h HAVE_IO_H)

check_function_exists(kill HAVE_KILL)
check_function_exists(killpg HAVE_KILLPG)
check_function_exists(kqueue HAVE_KQUEUE)
check_include_file(langinfo.h HAVE_LANGINFO_H)
option(HAVE_LARGEFILE_SUPPORT "Large file support for non linux")
check_function_exists(lchflags HAVE_LCHFLAGS)
check_function_exists(lchmod HAVE_LCHMOD)
check_function_exists(lchown HAVE_LCHOWN)
check_function_exists(lgamma HAVE_LGAMMA)
find_library(HAVE_LIBDL dl)
find_library(HAVE_LIBDLD dld)
find_library(HAVE_LIBIEEE ieee)
check_include_file(libintl.h HAVE_LIBINTL_H)
find_library(HAVE_LIBREADLINE readline)
find_library(HAVE_LIBRESOLV resolv)
find_library(HAVE_LIBSENDFILE sendfile)
check_include_file(libutil.h HAVE_LIBUTIL_H)
check_function_exists(link HAVE_LINK)
check_function_exists(linkat HAVE_LINKAT)
check_include_file(linux/can/bcm.h HAVE_LINUX_CAN_BCM_H)
check_include_file(linux/can.h HAVE_LINUX_CAN_H)
check_include_file(linux/can/j1939.h HAVE_LINUX_CAN_J1939_H)
option(HAVE_LINUX_CAN_RAW_FD_FRAMES "Define if compiling using Linux 3.6 or later" ON)
check_include_file(linux/can/raw.h HAVE_LINUX_CAN_RAW_H)
option(HAVE_LINUX_CAN_RAW_JOIN_FILTERS "Define if compiling using Linux 4.1 or later." ON)
check_include_file(linux/memfd.h HAVE_LINUX_MEMFD_H)
check_include_file(linux/netlink.h HAVE_LINUX_NETLINK_H)
check_include_file(linux/qrtr.h HAVE_LINUX_QRTR_H)
check_include_file(linux/random.h HAVE_LINUX_RANDOM_H)
check_include_file(linux/tipc.h HAVE_LINUX_TIPC_H)
check_include_file(linux/vm_sockets.h HAVE_LINUX_VM_SOCKETS_H)
check_include_file(linux/wait.h HAVE_LINUX_WAIT_H)
check_function_exists(lockf HAVE_LOCKF)
check_function_exists(log1p HAVE_LOG1P)
check_function_exists(log2 HAVE_LOG2)
check_type_size("long double" LONG_DOUBLE)
check_function_exists(lstat HAVE_LSTAT)
check_function_exists(lutimes HAVE_LUTIMES)
check_function_exists(madvise HAVE_MADVISE)
check_symbol_exists(makedev "sys/sysmacros.h" HAVE_MAKEDEV)
check_function_exists(mbrtowc HAVE_MBRTOWC)
check_function_exists(memfd_create HAVE_MEMFD_CREATE)
check_include_file(memory.h HAVE_MEMORY_H)
check_function_exists(memrchr HAVE_MEMRCHR)
check_function_exists(mkdirat HAVE_MKDIRAT)
check_function_exists(mkfifo HAVE_MKFIFO)
check_function_exists(mkfifoat HAVE_MKFIFOAT)
check_function_exists(mknod HAVE_MKNOD)
check_function_exists(mknodat HAVE_MKNODAT)
check_function_exists(mktime HAVE_MKTIME)
check_function_exists(mmap HAVE_MMAP)
check_function_exists(mremap HAVE_MREMAP)
check_include_file(ncurses.h HAVE_NCURSES_H)
check_include_file(ndir.h HAVE_NDIR_H)
check_include_file(netpacket/packet.h HAVE_NETPACKET_PACKET_H)
check_include_file(net/if.h HAVE_NET_IF_H)
check_function_exists(nice HAVE_NICE)
check_function_exists(openat HAVE_OPENAT)
check_function_exists(openpty HAVE_OPENPTY)
check_function_exists(pathconf HAVE_PATHCONF)
check_function_exists(pause HAVE_PAUSE)
check_function_exists(pipe2 HAVE_PIPE2)
check_function_exists(plock HAVE_PLOCK)
check_function_exists(poll HAVE_POLL)
check_include_file(poll.h HAVE_POLL_H)
check_function_exists(posix_fadvise HAVE_POSIX_FADVISE)
check_function_exists(posix_fallocate HAVE_POSIX_FALLOCATE)
check_function_exists(posix_spawn HAVE_POSIX_SPAWN)
check_function_exists(posix_spawnp HAVE_POSIX_SPAWNP)
check_function_exists(pread HAVE_PREAD)
check_function_exists(preadv HAVE_PREADV)
check_function_exists(preadv2 HAVE_PREADV2)
check_function_exists(prlimit HAVE_PRLIMIT)
check_include_file(process.h HAVE_PROCESS_H)
option(HAVE_PROTOTYPES "Define if your compiler supports function prototype" ON)
check_function_exists(pthread_condattr_setclock HAVE_PTHREAD_CONDATTR_SETCLOCK)
option(HAVE_PTHREAD_DESTRUCTOR "Defined for Solaris 2.6 bug in pthread header")
check_function_exists(pthread_getcpuclockid HAVE_PTHREAD_GETCPUCLOCKID)
check_include_file(pthread.h HAVE_PTHREAD_H)
check_function_exists(pthread_init HAVE_PTHREAD_INIT)
check_function_exists(pthread_kill HAVE_PTHREAD_KILL)
check_function_exists(pthread_sigmask HAVE_PTHREAD_SIGMASK)
check_include_file(pty.h HAVE_PTY_H)
check_function_exists(pwrite HAVE_PWRITE)
check_function_exists(pwritev HAVE_PWRITEV)
check_function_exists(pwritev2 HAVE_PWRITEV2)
check_function_exists(readlink HAVE_READLINK)
check_function_exists(readlinkat HAVE_READLINKAT)
check_function_exists(readv HAVE_READV)
check_function_exists(realpath HAVE_REALPATH)
check_function_exists(renameat HAVE_RENAMEAT)
option(HAVE_RL_APPEND_HISTORY "Define if readline supports append_history" ON)
option(HAVE_RL_CATCH_SIGNAL "Define if you can turn off readline's signal handling." ON)
option(HAVE_RL_COMPLETION_APPEND_CHARACTER "Define if you have readline 2.2" ON)
option(HAVE_RL_COMPLETION_DISPLAY_MATCHES_HOOK "Define if you have readline 4.0" ON)
option(HAVE_RL_COMPLETION_MATCHES "Define if you have readline 4.2" ON)
check_function_exists(rl_completion_suppress_append HAVE_RL_COMPLETION_SUPPRESS_APPEND)
option(HAVE_RL_PRE_INPUT_HOOK "Define if you have readline 4.0" ON)
option(HAVE_RL_RESIZE_TERMINAL "Define if you have readline 4.0" ON)
check_function_exists(round HAVE_ROUND)
check_function_exists(rtpSpawn HAVE_RTPSPAWN)
check_function_exists(sched_get_priority_max HAVE_SCHED_GET_PRIORITY_MAX)
check_include_file(sched.h HAVE_SCHED_H)
check_function_exists(sched_rr_get_interval HAVE_SCHED_RR_GET_INTERVAL)
check_function_exists(sched_setaffinity HAVE_SCHED_SETAFFINITY)
check_function_exists(sched_setparam HAVE_SCHED_SETPARAM)
check_function_exists(sched_setscheduler HAVE_SCHED_SETSCHEDULER)
check_function_exists(sem_getvalue HAVE_SEM_GETVALUE)
check_function_exists(sem_open HAVE_SEM_OPEN)
check_function_exists(sem_timedwait HAVE_SEM_TIMEDWAIT)
check_function_exists(sem_unlink HAVE_SEM_UNLINK)
check_function_exists(sendfile HAVE_SENDFILE)
check_function_exists(setegid HAVE_SETEGID)
check_function_exists(seteuid HAVE_SETEUID)
check_function_exists(setgid HAVE_SETGID)
check_function_exists(setgroups HAVE_SETGROUPS)
check_function_exists(sethostname HAVE_SETHOSTNAME)
check_function_exists(setitimer HAVE_SETITIMER)
check_function_exists(setlocale HAVE_SETLOCALE)
check_function_exists(setpgid HAVE_SETPGID)
check_function_exists(setpgrp HAVE_SETPGRP)
check_function_exists(setpriority HAVE_SETPRIORITY)
check_function_exists(setregid HAVE_SETREGID)
check_function_exists(setresgid HAVE_SETRESGID)
check_function_exists(setresuid HAVE_SETRESUID)
check_function_exists(setreuid HAVE_SETREUID)
check_function_exists(setsid HAVE_SETSID)
check_function_exists(setuid HAVE_SETUID)
check_function_exists(setvbuf HAVE_SETVBUF)
check_include_file(shadow.h HAVE_SHADOW_H)
check_function_exists(shm_open HAVE_SHM_OPEN)
check_function_exists(shm_unlink HAVE_SHM_UNLINK)
check_function_exists(sigaction HAVE_SIGACTION)
check_function_exists(sigaltstack HAVE_SIGALTSTACK)
check_function_exists(sigfillset HAVE_SIGFILLSET)
check_struct_has_member("siginfo_t" si_band siginfo_t.h HAVE_SIGINFO_T_SI_BAND)
check_function_exists(siginterrupt HAVE_SIGINTERRUPT)
check_include_file(signal.h HAVE_SIGNAL_H)
check_function_exists(sigpending HAVE_SIGPENDING)
check_function_exists(sigrelse HAVE_SIGRELSE)
check_function_exists(sigtimedwait HAVE_SIGTIMEDWAIT)
check_function_exists(sigwait HAVE_SIGWAIT)
check_function_exists(sigwaitinfo HAVE_SIGWAITINFO)
check_function_exists(snprintf HAVE_SNPRINTF)
list(APPEND CMAKE_EXTRA_INCLUDE_FILES sys/socket.h)
check_type_size("struct sockaddr_storage" SOCKADDR_STORAGE)
list(POP_BACK CMAKE_EXTRA_INCLUDE_FILES)

check_function_exists(socketpair HAVE_SOCKETPAIR)
check_include_file(spawn.h HAVE_SPAWN_H)
check_type_size("ssize_t" SSIZE_T)
check_function_exists(statvfs HAVE_STATVFS)


check_include_file(stdarg.h HAVE_STDARG_PROTOTYPES)
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(stdatomic.h HAVE_STD_ATOMIC)
check_function_exists(strdup HAVE_STRDUP)
check_function_exists(strftime HAVE_STRFTIME)
check_include_file(strings.h HAVE_STRINGS_H)
check_include_file(string.h HAVE_STRING_H)
check_function_exists(strlcpy HAVE_STRLCPY)
check_include_file(stropts.h HAVE_STROPTS_H)
check_function_exists(strsignal HAVE_STRSIGNAL)
check_struct_has_member("struct passwd" pw_gecos pwd.h HAVE_STRUCT_PASSWD_PW_GECOS)
check_struct_has_member("struct passwd" pw_passwd pwd.h HAVE_STRUCT_PASSWD_PW_PASSWD)
check_struct_has_member("struct stat" st_birthtime sys/stat.h HAVE_STRUCT_STAT_ST_BIRTHTIME)
check_struct_has_member("struct stat" st_blksize sys/stat.h HAVE_STRUCT_STAT_ST_BLKSIZE)
check_struct_has_member("struct stat" st_blocks sys/stat.h HAVE_STRUCT_STAT_ST_BLOCKS)
check_struct_has_member("struct stat" st_flags sys/stat.h HAVE_STRUCT_STAT_ST_FLAGS)
check_struct_has_member("struct stat" st_gen sys/stat.h HAVE_STRUCT_STAT_ST_GEN)
check_struct_has_member("struct stat" st_rdev sys/stat.h HAVE_STRUCT_STAT_ST_RDEV)
check_struct_has_member("struct tm" tm_zone time.h HAVE_STRUCT_TM_TM_ZONE)
check_function_exists(symlink HAVE_SYMLINK)
check_function_exists(symlinkat HAVE_SYMLINKAT)
check_function_exists(sync HAVE_SYNC)
check_function_exists(sysconf HAVE_SYSCONF)
check_include_file(sysexits.h HAVE_SYSEXITS_H)
check_include_file(sys/audioio.h HAVE_SYS_AUDIOIO_H)
check_include_file(sys/bsdtty.h HAVE_SYS_BSDTTY_H)
check_include_file(sys/devpoll.h HAVE_SYS_DEVPOLL_H)
check_include_file(sys/dir.h HAVE_SYS_DIR_H)
check_include_file(sys/endian.h HAVE_SYS_ENDIAN_H)
check_include_file(sys/epoll.h HAVE_SYS_EPOLL_H)
check_include_file(sys/event.h HAVE_SYS_EVENT_H)
check_include_file(sys/file.h HAVE_SYS_FILE_H)
check_include_file(sys/kern_control.h HAVE_SYS_KERN_CONTROL_H)
check_include_file(sys/loadavg.h HAVE_SYS_LOADAVG_H)
check_include_file(sys/lock.h HAVE_SYS_LOCK_H)
check_include_file(sys/memfd.h HAVE_SYS_MEMFD_H)
check_include_file(sys/mkdev.h HAVE_SYS_MKDEV_H)
check_include_file(sys/mman.h HAVE_SYS_MMAN_H)
check_include_file(sys/modem.h HAVE_SYS_MODEM_H)
check_include_file(sys/ndir.h HAVE_SYS_NDIR_H)
check_include_file(sys/param.h HAVE_SYS_PARAM_H)
check_include_file(sys/poll.h HAVE_SYS_POLL_H)
check_include_file(sys/random.h HAVE_SYS_RANDOM_H)
check_include_file(sys/resource.h HAVE_SYS_RESOURCE_H)
check_include_file(sys/select.h HAVE_SYS_SELECT_H)
check_include_file(sys/sendfile.h HAVE_SYS_SENDFILE_H)
check_include_file(sys/socket.h HAVE_SYS_SOCKET_H)
check_include_file(sys/statvfs.h HAVE_SYS_STATVFS_H)
check_include_file(sys/stat.h HAVE_SYS_STAT_H)
check_include_file(sys/syscall.h HAVE_SYS_SYSCALL_H)
check_include_file(sys/sysmacros.h HAVE_SYS_SYSMACROS_H)
check_include_file(sys/sys_domain.h HAVE_SYS_SYS_DOMAIN_H)
check_include_file(sys/termio.h HAVE_SYS_TERMIO_H)
check_include_file(sys/times.h HAVE_SYS_TIMES_H)
check_include_file(sys/time.h HAVE_SYS_TIME_H)
check_include_file(sys/types.h HAVE_SYS_TYPES_H)
check_include_file(sys/uio.h HAVE_SYS_UIO_H)
check_include_file(sys/un.h HAVE_SYS_UN_H)
check_include_file(sys/utsname.h HAVE_SYS_UTSNAME_H)
check_include_file(sys/wait.h HAVE_SYS_WAIT_H)
check_include_file(sys/xattr.h HAVE_SYS_XATTR_H)
check_function_exists(tcgetpgrp HAVE_TCGETPGRP)
check_function_exists(tcsetpgrp HAVE_TCSETPGRP)
check_function_exists(tempnam HAVE_TEMPNAM)
check_include_file(termios.h HAVE_TERMIOS_H)
check_include_file(term.h HAVE_TERM_H)
check_function_exists(tgamma HAVE_TGAMMA)
check_function_exists(timegm HAVE_TIMEGM)
check_function_exists(times HAVE_TIMES)
check_function_exists(tmpfile HAVE_TMPFILE)
check_function_exists(tmpnam HAVE_TMPNAM)
check_function_exists(tmpnam_r HAVE_TMPNAM_R)
check_function_exists(truncate HAVE_TRUNCATE)

find_library(tcl HAVE_UCS4_TCL)
check_function_exists(uname HAVE_UNAME)
check_include_file(unistd.h HAVE_UNISTD_H)
check_function_exists(unlinkat HAVE_UNLINKAT)
check_type_size("wchar_t" USABLE_WCHAR_T)
check_include_file(util.h HAVE_UTIL_H)
check_function_exists(utimensat HAVE_UTIMENSAT)
check_function_exists(utimes HAVE_UTIMES)
check_include_file(utime.h HAVE_UTIME_H)
check_function_exists(uuid_create HAVE_UUID_CREATE)
check_function_exists(uuid_enc_be HAVE_UUID_ENC_BE)
check_function_exists(uuid_generate_time_safe HAVE_UUID_GENERATE_TIME_SAFE)
check_include_file(uuid.h HAVE_UUID_H)
check_include_file(uuid/uuid.h HAVE_UUID_UUID_H)
check_function_exists(wait3 HAVE_WAIT3)
check_function_exists(wait4 HAVE_WAIT4)
check_function_exists(waitid HAVE_WAITID)
check_function_exists(waitpid HAVE_WAITPID)
check_include_file(wchar.h HAVE_WCHAR_H)
check_function_exists(wcscoll HAVE_WCSCOLL)
check_function_exists(wcsftime HAVE_WCSFTIME)
check_function_exists(wcsxfrm HAVE_WCSXFRM)
check_function_exists(wmemcmp HAVE_WMEMCMP)
option(HAVE_WORKING_TZSET "Define if tzset() actually switches the local timezone in a meaningful way" ON)
check_function_exists(writev HAVE_WRITEV)
check_library_exists(libssl X509_VERIFY_PARAM_set1_host "/usr/lib" HAVE_X509_VERIFY_PARAM_SET1_HOST)
check_library_exists(zlib inflateCopy lib HAVE_ZLIB_COPY)
check_function_exists(_getpty HAVE__GETPTY)
check_symbol_exists(major "mkdev" MAJOR_IN_MKDEV)
check_symbol_exists(major "sys/sysmacros.h" MAJOR_IN_SYSMACROS)
check_symbol_exists(mvwdelch "curses.h" MVWDELCH_IS_EXPRESSION)
set(PACKAGE_BUGREPORT "https://github.com/Denzy7/cpython-lite")
set(PACKAGE_NAME "cpython-lite")
set(PACKAGE_STRING "cpython-lite.3.9.4")
set(PACKAGE_TARNAME "Python-3.9.4.tar.xz")
set(PACKAGE_URL "https://github.com/Denzy7/cpython-lite")
set(PACKAGE_VERSION "3.9.4")
option(POSIX_SEMAPHORES_NOT_ENABLED "Define if POSIX semaphores aren't enabled on your system" OFF)
option(PTHREAD_KEY_T_IS_COMPATIBLE_WITH_INT "Define if pthread_key_t is compatible with int" 1)
check_symbol_exists(PTHREAD_SCOPE_SYSTEM "pthread.h" PTHREAD_SYSTEM_SCHED_SUPPORTED)

set(PY_BUILTIN_HASHLIB_HASHES "md5,sha1,sha256" CACHE STRING "enabled builtin hash modules")
set(PY_SSL_DEFAULT_CIPHERS "1" CACHE STRING "Default cipher suites list for ssl module. 1: Python's preferred selection, 2: leave OpenSSL defaults untouched, 0: custom string")

option(Py_DEBUG "Define if you want to build an interpreter with many run-time checks." NO)
option(Py_ENABLE_SHARED "Defined if Python is built as a shared library." ${BUILD_SHARED_LIBS})


set(RETSIGTYPE "void" CACHE STRING "assume C89 semantics that RETSIGTYPE is always void")



check_type_size("double" SIZEOF_DOUBLE)
check_type_size("float" SIZEOF_FLOAT)
list(APPEND CMAKE_EXTRA_INCLUDE_FILES stdio.h)
check_type_size("fpos_t" SIZEOF_FPOS_T)
list(POP_BACK CMAKE_EXTRA_INCLUDE_FILES)
check_type_size("int" SIZEOF_INT)
check_type_size("long" SIZEOF_LONG)
check_type_size("long double" SIZEOF_LONG_DOUBLE)
check_type_size("long long" SIZEOF_LONG_LONG)
check_type_size("off_t" SIZEOF_OFF_T)
check_type_size("pid_t" SIZEOF_PID_T)
check_type_size("pthread_key_t" SIZEOF_PTHREAD_KEY_T)
check_type_size("pthread_t" SIZEOF_PTHREAD_T)
check_type_size("short" SIZEOF_SHORT)
check_type_size("size_t" SIZEOF_SIZE_T)
check_type_size("time_t" SIZEOF_TIME_T)
check_type_size("uintptr_t" SIZEOF_UINTPTR_T)
check_type_size("void *" SIZEOF_VOID_P)
check_type_size("wchar_t" SIZEOF_WCHAR_T)
check_type_size("_Bool" SIZEOF__BOOL)
option(STDC_HEADERS "Define to 1 if you have the ANSI C header files" 1)
option(SYS_SELECT_WITH_SYS_TIME "Define if you can safely include both <sys/select.h> and <sys/time.h> (which you can't on SCO ODT 3.0)" 1)
option(USE_COMPUTED_GOTOS "Define if you want to use computed gotos in ceval.c" 1)
option(TIME_WITH_SYS_TIME "Define to 1 if you can safely include both <sys/time.h> and <time.h>." 1)
option(WITH_DECIMAL_CONTEXTVAR "build the _decimal module using a coroutine-local rather than a thread-local context" 1)
option(WITH_DOC_STRINGS "Define if you want documentation strings in extension modules" 1)
option(cmakedefine "Define if you want to compile in DTrace support" 0)
check_struct_has_member("WINDOW" _flags curses.h WINDOW_HAS_FLAGS)


option(WITH_PYMALLOC "Define if you want to compile in Python-specific mallocs" 1)
set(PREFIX ${CMAKE_PREFIX_PATH})
configure_file(pyconfig.h.in config/pyconfig.h @ONLY)

#############################
#           BUILD           #
#############################
include_directories(
    ${PYSRC}/Include
    ${PYSRC}/Include/internal
    ${PYSRC}/Python
    ${PYSRC}/Modules
    PC
    ${CMAKE_CURRENT_BINARY_DIR}/config
)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPy_BUILD_CORE -DPy_BUILD_CORE_BUILTIN")
#the loader used to load static libraries (.dll, .so)
if(WIN32)
        set(lib_loader dynload_win.c)
else()
        set(lib_loader dynload_shlib.c)
endif()

#a path module for path resolution
if(WIN32)
        set(path_module PC/getpathp.c)
else()
        set(path_module Modules/getpath.c)
endif()

#default modules
set(default_modules
                ${path_module}
                Modules/main.c
                Modules/gcmodule.c

                Modules/_io/_iomodule.c

                Modules/_io/iobase.c
                Modules/_io/fileio.c
                Modules/_io/bufferedio.c
                Modules/_io/textio.c
                Modules/_io/bytesio.c
                Modules/_io/stringio.c

                #get build info
                Modules/getbuildinfo.c
                )

#parser
set(parser
                Parser/pegen/pegen.c
                Parser/pegen/parse.c
                Parser/pegen/parse_string.c
                Parser/pegen/peg_api.c

                Parser/acceler.c
                Parser/grammar1.c
                Parser/listnode.c
                Parser/node.c
                Parser/parser.c
                Parser/token.c
                )

#default python
set(default_python
                Python/_warnings.c
                Python/Python-ast.c
                Python/asdl.c
                Python/ast.c
                Python/ast_opt.c
                Python/ast_unparse.c
                Python/bltinmodule.c
                Python/ceval.c
                Python/codecs.c
                Python/compile.c
                Python/context.c
                Python/dynamic_annotations.c
                Python/errors.c
                #frozenmain.c causes link errors on win32
                #Python/frozenmain.c
                Python/future.c
                Python/getargs.c
                Python/getcompiler.c
                Python/getcopyright.c
                Python/getplatform.c
                Python/getversion.c
                Python/graminit.c
                Python/hamt.c
                Python/hashtable.c
                Python/import.c
                Python/importdl.c
                Python/initconfig.c
                Python/marshal.c
                Python/modsupport.c
                Python/mysnprintf.c
                Python/mystrtoul.c
                Python/pathconfig.c
                Python/peephole.c
                Python/preconfig.c
                Python/pyarena.c
                Python/pyctype.c
                Python/pyfpe.c
                Python/pyhash.c
                Python/pylifecycle.c
                Python/pymath.c
                Python/pystate.c
                Python/pythonrun.c
                Python/pytime.c
                Python/bootstrap_hash.c
                Python/structmember.c
                Python/symtable.c
                Python/sysmodule.c
                Python/thread.c
                Python/traceback.c
                Python/getopt.c
                Python/pystrcmp.c
                Python/pystrtod.c
                Python/pystrhex.c
                Python/dtoa.c
                Python/formatter_unicode.c
                Python/fileutils.c

                #lib loader
                Python/${lib_loader}

                #freezing modules
                Python/frozen.c
                )

#python types/objects
set(python_objects
                Objects/abstract.c
                Objects/accu.c
                Objects/boolobject.c
                Objects/bytes_methods.c
                Objects/bytearrayobject.c
                Objects/bytesobject.c
                Objects/call.c
                Objects/capsule.c
                Objects/cellobject.c
                Objects/classobject.c
                Objects/codeobject.c
                Objects/complexobject.c
                Objects/descrobject.c
                Objects/enumobject.c
                Objects/exceptions.c
                Objects/genericaliasobject.c
                Objects/genobject.c
                Objects/fileobject.c
                Objects/floatobject.c
                Objects/frameobject.c
                Objects/funcobject.c
                Objects/interpreteridobject.c
                Objects/iterobject.c
                Objects/listobject.c
                Objects/longobject.c
                Objects/dictobject.c
                Objects/odictobject.c
                Objects/memoryobject.c
                Objects/methodobject.c
                Objects/moduleobject.c
                Objects/namespaceobject.c
                Objects/object.c
                Objects/obmalloc.c
                Objects/picklebufobject.c
                Objects/rangeobject.c
                Objects/setobject.c
                Objects/sliceobject.c
                Objects/structseq.c
                Objects/tupleobject.c
                Objects/typeobject.c
                Objects/unicodeobject.c
                Objects/unicodectype.c
                Objects/weakrefobject.c
                )

#note, python should build without any extra modules and be able to get basic functions like
#Py_GetBuildInfo()
#Py_GetCompiler()
#Py_GetPlatform()
#etc... see https://docs.python.org/3/c-api/init.html

#however we need extra modules to be able to fire up and interpretor (or even call Py_Initialize() and other cool functions!)
#we namely need a
#signal+faults handler, parser+tokenizer, memory allocator, threading, weakref, io and codecs
#and of course several os modules
#this will depend on your system and will determine how python runs the system

#strangely enough, the os module is Modules/posixmodule.c
#it contains both linux and windows functions. The catch is that it uses config/{os}/pyconfig.h and config/{os}/config.c to find OS functions which needs
#an extensive configuration process. Find a specially tailored pyconfig.h's for several systems in config directory
#these are put here below

set(extra_modules
                #signal (interupts etc...)
                Modules/signalmodule.c
                #faulthandler
                Modules/faulthandler.c

                #tokenizer and parser to read python code. Include a readline module too
                Parser/parsetok.c
                Parser/tokenizer.c
                Modules/_peg_parser.c
                Parser/myreadline.c

                #memalloc (traces memory allocations)
                Modules/_tracemalloc.c

                #threads
                Modules/_threadmodule.c

                #weakref functionality
                Modules/_weakref.c

                #input/output
                Modules/_io/_iomodule.c

                #codecs/encodings
                Modules/_codecsmodule.c

                #os modules (posix) down below

                #and that's it! Py_Main and Py_Initialize should now work!

                #below are some 3 extra modules you need to get round an
                #import hook if embedding python to an application(really recommended)
                Modules/itertoolsmodule.c
                Modules/_collectionsmodule.c
                Modules/_sre.c

                #add any more modules to bake into python here...(optional)

                Modules/atexitmodule.c

                #math module
                Modules/mathmodule.c
                Modules/_math.c

                #time for zlib
                Modules/timemodule.c

                )

#file with modules configuration. Edit this file to add/remove modules to be baked
#this is also a chance to patch on top of Win32 modules to add some important stuff
set(modules_config config.c)
if(WIN32)
        list(APPEND default_modules
                Modules/_io/winconsoleio.c
                #frozen_dllmain.c causes linking errors mingw
                #PC/frozen_dllmain.c
                PC/dl_nt.c
                PC/winreg.c
                Modules/_winapi.c
                )
endif()

if(HAVE_LIBZ)
    list(APPEND extra_modules Modules/zlibmodule.c)
endif()

set(stdlib_modules
    #these are modules needed by stdlib as very added bonus but
    #no needed unless you need them. these are the very needed
    #cross platform ones
    Modules/errnomodule.c
    Modules/selectmodule.c
    Modules/_struct.c
    Modules/binascii.c
    Modules/_csv.c
    Modules/_datetimemodule.c
    Modules/_heapqmodule.c
    Modules/_json.c
    Modules/arraymodule.c
)

if(HAVE_LIBSQLITE3)
    set(pysqlite3_src
        ${PYSRC}/Modules/_sqlite/module.c
        ${PYSRC}/Modules/_sqlite/connection.c
        ${PYSRC}/Modules/_sqlite/cache.c
        ${PYSRC}/Modules/_sqlite/cursor.c
        ${PYSRC}/Modules/_sqlite/microprotocols.c
        ${PYSRC}/Modules/_sqlite/prepare_protocol.c
        ${PYSRC}/Modules/_sqlite/row.c
        ${PYSRC}/Modules/_sqlite/statement.c
        ${PYSRC}/Modules/_sqlite/util.c
    )

    add_library(pysqlite3 STATIC ${pysqlite3_src})
    target_compile_definitions(pysqlite3 PRIVATE MODULE_NAME="sqlite3")
endif(
)
#if(HAVE_LIBFFI)
#    #ctypes. broken on win32
#    list(APPEND stdlib_modules
#        Modules/_ctypes/_ctypes.c
#        Modules/_ctypes/callproc.c
#        Modules/_ctypes/stgdict.c
#        Modules/_ctypes/cfield.c
#        Modules/_ctypes/callbacks.c
#    )
#endif()

if(UNIX)
    #some stdlib modules for UNIX
    list(APPEND stdlib_modules
        Modules/_posixsubprocess.c

    )
    if(HAVE_LIBREADLINE)
        list(APPEND stdlib_modules Modules/readline.c)
    endif()
endif()



set(hashing_modules
    #blake2
    Modules/_blake2/blake2module.c
    Modules/_blake2/blake2b_impl.c
    Modules/_blake2/blake2s_impl.c

    #md5
    Modules/md5module.c

    #sha
    Modules/sha1module.c
    Modules/sha256module.c
    Modules/sha512module.c
    Modules/_sha3/sha3module.c
)

#blake2 hashing


set(PYSRCS
        #comment this out to remove extra modules from build (use with caution)
        ${modules_config}

        #this is a patched posixmodule and socketmodule for mingw
        posixmodule.c
        socketmodule.c
        )

foreach(PYSRCFILE IN LISTS
        default_modules
        parser
        default_python
        python_objects
        extra_modules
        stdlib_modules
        hashing_modules)
        list(APPEND PYSRCS "${PYSRC}/${PYSRCFILE}")
endforeach()

#add the infamous python library
add_library(cpython-portable ${PYSRCS})
set_target_properties(cpython-portable PROPERTIES
                      POSITION_INDEPENDENT_CODE ON)


if(WIN32)
    target_link_libraries(cpython-portable ws2_32 version pathcch iphlpapi)
else()
    target_link_libraries(cpython-portable dl m)
    if(HAVE_LIBUTIL)
        target_link_libraries(cpython-portable ${HAVE_LIBUTIL})
    endif()
endif()

if(HAVE_LIBZ)
    target_link_libraries(cpython-portable ${HAVE_LIBZ})
endif()
if(HAVE_LIBREADLINE)
    target_link_libraries(cpython-portable ${HAVE_LIBREADLINE})
endif()
if(HAVE_LIBFFI)
    target_link_libraries(cpython-portable ${HAVE_LIBFFI})
endif()
if(HAVE_LIBSQLITE3)
    target_link_libraries(pysqlite3 ${HAVE_LIBSQLITE3})
    target_link_libraries(cpython-portable  pysqlite3)
endif()
