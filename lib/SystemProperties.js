const {
    BaseProperties
} = require("bindings")("android-os.node");

class SystemProperties extends BaseProperties {
    static TAG = "NodeSystemProperties";
    static PROP_VALUE_MAX = 91;
    static TRACK_KEY_ACCESS = false;

    constructor() {
        super();
    }

    static get(key, def) {
        return this.native_get(key, def);
    }

    static getList(key, sep = ",") {
        if (typeof key != "string") {
            throw new TypeError("The key should be an string");
        }

        if (typeof sep != "string") {
            throw new TypeError("The separator should be an string");
        }

        const result = this.get(key, "");

        return result != "" ? result.split(sep) : [];
    }

    static getBoolean(key, def) {
        return this.native_getBoolean(key, def);
    }

    static getInt(key, def) {
        return this.native_getInt(key, def);
    }

    static set(key, val) {
        if (typeof key != "string") {
            throw new TypeError("The key should be an string");
        }

        if (val != null && !key.startsWith("ro.") && val.length > this.PROP_VALUE_MAX) {
            throw new Error("value of system property '" + key + "' is longer than " + this.PROP_VALUE_MAX + " bytes: " + val);
        }

        super.set(key, String(val));
    }

    static native_get(key, def = "") {
        return super.native_get(key, def)
    }
    
    static native_getBoolean(key, def = false) {
        return super.native_getBoolean(key, def)
    }
    
    static native_getInt(key, def = 0) {
        return super.native_getInt(key, def)
    }
}

module.exports = {
    SystemProperties
};