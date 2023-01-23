import { Build, System } from '@android/os'

class Magisk {
  static LOGFILE = "/cache/magisk.log";
  static UNBLOCKFILE = "/dev/.magisk_unblock";
  static SECURE_DIR = "/data/adb";
  static MODULEROOT = this.SECURE_DIR + "/modules";
  static MODULEUPGRADE = this.SECURE_DIR + "/modules_update";
  static DATABIN = this.SECURE_DIR + "/magisk";
  static MAGISKDB = this.SECURE_DIR + "/magisk.db";

  // tmpfs paths
  static MAGISKTMP = System.cmd('magisk --path');
  static INTLROOT = ".magisk";
  static MIRRDIR = this.INTLROOT + "/mirror";
  static RULESDIR = this.MIRRDIR + "/sepolicy.rules";
  static BLOCKDIR = this.INTLROOT + "/block";
  static WORKERDIR = this.INTLROOT + "/worker";
  static MODULEMNT = this.INTLROOT + "/modules";
  static BBPATH = this.INTLROOT + "/busybox";
  static ROOTOVL = this.INTLROOT + "/rootdir";
  static SHELLPTS = this.INTLROOT + "/pts";
  static ROOTMNT = this.ROOTOVL + "/.mount_list";
  static ZYGISKBIN = this.INTLROOT + "/zygisk";
  static SELINUXMOCK = this.INTLROOT + "/selinux";
  static APP_DATA_DIR = (Build.SDK >= 24 ? "/data/user_de" : "/data/user");
}