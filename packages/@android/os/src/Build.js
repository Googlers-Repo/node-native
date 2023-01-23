import {SystemProperties} from './SystemProperties.js'

class Build {
  static TAG = "Build";
  static UNKNOWN = "unknown";
  static ID = SystemProperties.get("ro.build.id");
  static DISPLAY = SystemProperties.get("ro.build.display.id");
  static PRODUCT = SystemProperties.get("ro.product.name");
  static DEVICE = SystemProperties.get("ro.product.device");
  static BOARD = SystemProperties.get("ro.product.board");
  static MANUFACTURER = SystemProperties.get("ro.product.manufacturer");
  static BRAND = SystemProperties.get("ro.product.brand");
  static MODEL = SystemProperties.get("ro.product.model");
  static BOOTLOADER = SystemProperties.get("ro.bootloader");
  static HARDWARE = SystemProperties.get("ro.hardware");
  static SKU = SystemProperties.get("ro.boot.hardware.sku");
  static ODM_SKU = SystemProperties.get("ro.boot.product.hardware.sku");
  static IS_EMULATOR = SystemProperties.get("ro.boot.qemu") === "1";
  static SERIAL = SystemProperties.get("no.such.thing");
  static SUPPORTED_ABIS = SystemProperties.get("ro.product.cpu.abilist").split(',');
  static SUPPORTED_32_BIT_ABIS = SystemProperties.getList("ro.product.cpu.abilist32", ',')
  static SUPPORTED_64_BIT_ABIS = SystemProperties.getList("ro.product.cpu.abilist64", ',')
  static VERSION = class {
    static INCREMENTAL = SystemProperties.get("ro.build.version.incremental");
    static RELEASE = SystemProperties.get("ro.build.version.release");
    static RELEASE_OR_CODENAME = SystemProperties.get("ro.build.version.release_or_codename");
    static RELEASE_OR_PREVIEW_DISPLAY = SystemProperties.get("ro.build.version.release_or_preview_display");
    static BASE_OS = SystemProperties.get("ro.build.version.base_os", "");
    static SECURITY_PATCH = SystemProperties.get("ro.build.version.security_patch", "");
    static SDK = SystemProperties.getNumber("ro.build.version.sdk", 0);
    static CODENAME = SystemProperties.get("ro.build.version.codename");
    static KNOWN_CODENAMES = SystemProperties.getList("ro.build.version.known_codenames", ",")
    static ALL_CODENAMES = SystemProperties.getList("ro.build.version.all_codenames", ",");
    static MIN_SUPPORTED_TARGET_SDK_INT = SystemProperties.getNumber("ro.build.version.min_supported_target_sdk", 0);
  }
  static VERSION_CODES = class {
    static BASE = 1;
    static BASE_1_1 = 2;
    static CUPCAKE = 3;
    static DONUT = 4;
    static ECLAIR = 5;
    static ECLAIR_0_1 = 6;
    static ECLAIR_MR1 = 7;
    static FROYO = 8;
    static GINGERBREAD = 9;
    static GINGERBREAD_MR1 = 10;
    static HONEYCOMB = 11;
    static HONEYCOMB_MR1 = 12;
    static HONEYCOMB_MR2 = 13;
    static ICE_CREAM_SANDWICH = 14;
    static ICE_CREAM_SANDWICH_MR1 = 15;
    static JELLY_BEAN = 16;
    static JELLY_BEAN_MR1 = 17;
    static JELLY_BEAN_MR2 = 18;
    static KITKAT = 19;
    static KITKAT_WATCH = 20;
    static L = 21;
    static LOLLIPOP = 21;
    static LOLLIPOP_MR1 = 22;
    static M = 23;
    static N = 24;
    static N_MR1 = 25;
    static O = 26;
    static O_MR1 = 27;
    static P = 28;
    static Q = 29;
    static R = 30;
    static S = 31;
    static S_V2 = 32;
    static TIRAMISU = 33;
  }
  static TYPE = SystemProperties.get("ro.build.type");
  static TAGS = SystemProperties.get("ro.build.tags");
  static FINGERPRINT = this.deriveFingerprint();
  static deriveFingerprint() {
    const finger = SystemProperties.get("ro.build.fingerprint", "");
    if (finger === "") {
      finger = SystemProperties.get("ro.product.brand") + '/' +
        SystemProperties.get("ro.product.name") + '/' +
        SystemProperties.get("ro.product.device") + ':' +
        SystemProperties.get("ro.build.version.release") + '/' +
        SystemProperties.get("ro.build.id") + '/' +
        SystemProperties.get("ro.build.version.incremental") + ':' +
        SystemProperties.get("ro.build.type") + '/' +
        SystemProperties.get("ro.build.tags");
    }
    return finger;
  }
  static HW_TIMEOUT_MULTIPLIER = SystemProperties.getNumber("ro.hw_timeout_multiplier", 1);
  static IS_TREBLE_ENABLED = SystemProperties.getBoolean("ro.treble.enabled", false);
  static TIME = SystemProperties.getNumber("ro.build.date.utc") * 1000;
  static USER = SystemProperties.get("ro.build.user");
  static HOST = SystemProperties.get("ro.build.host");
  static IS_DEBUGGABLE = SystemProperties.getNumber("ro.debuggable", 0) == 1;
  static IS_ARC = SystemProperties.getBoolean("ro.boot.container", false);
}

export  {Build};