cmd_/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/it6604.o := arm-hisiv100nptl-linux-gcc -Wp,-MD,/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/.it6604.o.d  -nostdinc -isystem /opt/hisi-linux-nptl/arm-hisiv100-linux/bin/../lib/gcc/arm-hisiv100-linux-uclibcgnueabi/4.4.1/include -I/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-hi3520d/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DHI_XXXX -I/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/../gpio-i2c_8b  -DMODULE  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(it6604)"  -D"KBUILD_MODNAME=KBUILD_STR(it6604)" -c -o /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/it6604.o /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/it6604.c

source_/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/it6604.o := /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/it6604.c

deps_/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/it6604.o := \
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
  include/linux/version.h \
  include/linux/module.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  include/linux/stat.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/stat.h \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  include/linux/seqlock.h \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  include/linux/stringify.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  include/linux/spinlock_types_up.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  include/linux/rwlock_types.h \
  include/linux/spinlock_up.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/hw_breakpoint.h \
  include/linux/rwlock.h \
  include/linux/spinlock_api_up.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/atomic.h \
    $(wildcard include/config/generic/atomic64.h) \
  include/asm-generic/atomic-long.h \
  include/linux/math64.h \
  include/linux/kmod.h \
  include/linux/gfp.h \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/linux/wait.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/current.h \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/linux/nodemask.h \
  include/linux/bitmap.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/string.h \
  include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/glue.h \
  include/asm-generic/getorder.h \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  include/linux/notifier.h \
  include/linux/errno.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  include/linux/rwsem-spinlock.h \
  include/linux/srcu.h \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/pfn.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/percpu.h \
  include/asm-generic/percpu.h \
  include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/topology.h \
  include/asm-generic/topology.h \
  include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/jiffies.h \
  include/linux/timex.h \
  include/linux/param.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/timex.h \
  arch/arm/mach-hi3520d/include/mach/timex.h \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  include/linux/sysctl.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/preempt/rt.h) \
  include/linux/completion.h \
  include/linux/rcutiny.h \
  include/linux/elf.h \
  include/linux/elf-em.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/elf.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/user.h \
  include/linux/kobject.h \
  include/linux/sysfs.h \
  include/linux/kobject_ns.h \
  include/linux/kref.h \
  include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  include/linux/tracepoint.h \
  include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/module.h \
    $(wildcard include/config/arm/unwind.h) \
  include/trace/events/module.h \
  include/trace/define_trace.h \
  include/linux/fcntl.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/fcntl.h \
  include/asm-generic/fcntl.h \
  include/linux/mm.h \
    $(wildcard include/config/sysctl.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/hugetlbfs.h) \
  include/linux/rbtree.h \
  include/linux/prio_tree.h \
  include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mm/owner.h) \
    $(wildcard include/config/mmu/notifier.h) \
  include/linux/auxvec.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/auxvec.h \
  include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
  include/linux/range.h \
  include/linux/bit_spinlock.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/pgtable.h \
    $(wildcard include/config/highpte.h) \
  include/asm-generic/4level-fixup.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/proc-fns.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/glue-proc.h \
    $(wildcard include/config/cpu/arm610.h) \
    $(wildcard include/config/cpu/arm7tdmi.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/cpu/arm720t.h) \
    $(wildcard include/config/cpu/arm740t.h) \
    $(wildcard include/config/cpu/arm9tdmi.h) \
    $(wildcard include/config/cpu/arm920t.h) \
    $(wildcard include/config/cpu/arm922t.h) \
    $(wildcard include/config/cpu/arm925t.h) \
    $(wildcard include/config/cpu/arm926t.h) \
    $(wildcard include/config/cpu/arm940t.h) \
    $(wildcard include/config/cpu/arm946e.h) \
    $(wildcard include/config/cpu/arm1020.h) \
    $(wildcard include/config/cpu/arm1020e.h) \
    $(wildcard include/config/cpu/arm1022.h) \
    $(wildcard include/config/cpu/arm1026.h) \
    $(wildcard include/config/cpu/mohawk.h) \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/cpu/v6k.h) \
    $(wildcard include/config/cpu/v7.h) \
  arch/arm/mach-hi3520d/include/mach/vmalloc.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/pgtable-hwdef.h \
  include/asm-generic/pgtable.h \
  include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/s390.h) \
  include/linux/huge_mm.h \
  include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
  include/linux/vm_event_item.h \
  include/linux/miscdevice.h \
  include/linux/major.h \
  include/linux/proc_fs.h \
    $(wildcard include/config/proc/devicetree.h) \
    $(wildcard include/config/proc/kcore.h) \
  include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/slab.h) \
  include/linux/slub_def.h \
    $(wildcard include/config/slub/stats.h) \
    $(wildcard include/config/slub/debug.h) \
  include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  include/linux/fs.h \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  include/linux/limits.h \
  include/linux/ioctl.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/linux/blk_types.h \
    $(wildcard include/config/blk/dev/integrity.h) \
  include/linux/kdev_t.h \
  include/linux/dcache.h \
  include/linux/rculist.h \
  include/linux/rculist_bl.h \
  include/linux/list_bl.h \
  include/linux/path.h \
  include/linux/radix-tree.h \
  include/linux/pid.h \
  include/linux/capability.h \
  include/linux/semaphore.h \
  include/linux/fiemap.h \
  include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  include/linux/percpu_counter.h \
  include/linux/dqblk_xfs.h \
  include/linux/dqblk_v1.h \
  include/linux/dqblk_v2.h \
  include/linux/dqblk_qtree.h \
  include/linux/nfs_fs_i.h \
  include/linux/nfs.h \
  include/linux/sunrpc/msg_prot.h \
  include/linux/inet.h \
  include/linux/err.h \
  include/linux/magic.h \
  include/linux/kthread.h \
  include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/cgroup/sched.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/cputime.h \
  include/asm-generic/cputime.h \
  include/linux/sem.h \
  include/linux/ipc.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/ipcbuf.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/sembuf.h \
  include/linux/signal.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/signal.h \
  include/asm-generic/signal-defs.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/sigcontext.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/linux/proportions.h \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/resource.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/resource.h \
  include/asm-generic/resource.h \
  include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  include/linux/timerqueue.h \
  include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  include/linux/latencytop.h \
  include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/user/ns.h) \
  include/linux/key.h \
  include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  include/linux/aio.h \
  include/linux/aio_abi.h \
  include/linux/uio.h \
  include/linux/delay.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/delay.h \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  include/linux/ioport.h \
  include/linux/klist.h \
  include/linux/pm.h \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/pm/runtime.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/device.h \
    $(wildcard include/config/dmabounce.h) \
  include/linux/pm_wakeup.h \
  include/linux/platform_device.h \
    $(wildcard include/config/suspend.h) \
    $(wildcard include/config/hibernate/callbacks.h) \
  include/linux/mod_devicetable.h \
  include/linux/cdev.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/uaccess.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/io.h \
  arch/arm/mach-hi3520d/include/mach/io.h \
  include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  include/linux/irqreturn.h \
  include/linux/irqnr.h \
  include/linux/hardirq.h \
  include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/hardirq.h \
    $(wildcard include/config/local/timers.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/irq.h \
  arch/arm/mach-hi3520d/include/mach/irqs.h \
  include/linux/irq_cpustat.h \
  include/trace/events/irq.h \
  include/linux/poll.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/osdrv/kernel/linux-3.0.y/arch/arm/include/asm/poll.h \
  include/asm-generic/poll.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/gpio_i2c.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/it6604.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/hdmirx.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/mcu.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/config.h \
    $(wildcard include/config/h/.h) \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/typedef.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/debug.h \
  /home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/io.h \

/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/it6604.o: $(deps_/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/it6604.o)

$(deps_/home/zhouhua/work/Hi3520D_SDK_V1.0.2.2/mpp/extdrv/it6604/it6604.o):
