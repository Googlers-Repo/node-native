import { createRequire } from 'module';
import util from 'util'

const require = createRequire(import.meta.url);
const { __android_log_write } = require("/data/data/io.spck/files/android-log/build/Release/android-util.node");

class Log {
  static VERBOSE = 2;
  static DEBUG = 3;
  static INFO = 4;
  static WARN = 5;
  static ERROR = 6;
  static v(tag, msg, ...data) {
    __android_log_write(this.VERBOSE, String(tag), util.format(msg, ...data));
  }
  static d(tag, msg, ...data) {
    __android_log_write(this.DEBUG, String(tag), util.format(msg, ...data));
  }
  static i(tag, msg, ...data) {
    __android_log_write(this.INFO, String(tag), util.format(msg, ...data));
  }
  static w(tag, msg, ...data) {
    __android_log_write(this.WARN, String(tag), util.format(msg, ...data));
  }
  static e(tag, msg, ...data) {
    __android_log_write(this.ERROR, String(tag), util.format(msg, ...data));
  }
}

export  {Log};