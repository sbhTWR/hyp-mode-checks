#include <linux/module.h>
#include <linux/kernel.h>

#include <asm/virt.h>

/**
 * Simple extension for early kernels that prints whether virtualization
 * is available. Copied from 4.7 arch/arm/kernel/setup.c.
 */
static int __init check_hyp_and_exit(void)
{
    if (is_hyp_mode_available()) {
            pr_info("CPU: All CPU(s) started in HYP or EL2 mode.\n");
            pr_info("CPU: Virtualization extensions available.\n");
    } else if (is_hyp_mode_mismatched()) {
            pr_warn("CPU: WARNING: CPU(s) started in wrong/inconsistent modes!\n");
            pr_warn("CPU: This may indicate a broken bootloader or firmware.\n");
    } else
            pr_info("CPU: All CPU(s) started in SVC or EL1 mode.\n");

    /* We don't actually use this subsystem. */
    return ENODEV;
}

subsys_initcall(check_hyp_and_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Quick hypervisor check utility for ARMv7/ARMv8.");
