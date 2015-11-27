cmd_/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.o := arm-hisiv100nptl-linux-gcc -Wp,-MD,/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/.hdmirx.o.d  -nostdinc -isystem /opt/hisi-linux-nptl/arm-hisiv100-linux/bin/../lib/gcc/arm-hisiv100-linux-uclibcgnueabi/4.4.1/include -I/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-hi3520d/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DHI_XXXX -I/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/../gpio-i2c_8b  -DMODULE  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(hdmirx)"  -D"KBUILD_MODNAME=KBUILD_STR(hdmirx)" -c -o /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.o /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.c

source_/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.o := /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.c

deps_/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.o := \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/mcu.h \
  include/linux/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /opt/hisi-linux-nptl/arm-hisiv100-linux/bin/../lib/gcc/arm-hisiv100-linux-uclibcgnueabi/4.4.1/include/stdarg.h \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/linkage.h \
  include/linux/stddef.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/posix_types.h \
  include/linux/bitops.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/bitops.h \
    $(wildcard include/config/smp.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/system.h \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/linux/typecheck.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/irqflags.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/hwcap.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/memory.h \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/arm/patch/phys/virt/16bit.h) \
  include/linux/const.h \
  arch/arm/mach-hi3520d/include/mach/memory.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/sizes.h \
  include/asm-generic/sizes.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  include/asm-generic/cmpxchg-local.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/swab.h \
  include/linux/byteorder/generic.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  include/linux/dynamic_debug.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/div64.h \
  include/linux/errno.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/config.h \
    $(wildcard include/config/h/.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/typedef.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/debug.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/io.h \

/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.o: $(deps_/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.o)

$(deps_/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.o):
