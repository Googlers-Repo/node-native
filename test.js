const { System, SystemProperties, Build, Environment } = require(".");
//const { BaseSeLinux } = require("bindings")("android-util.node");

// console.log(System.uname())

// Should throw error
// System.cmd("cmd battery reset -f")

//const locked = SystemProperties.native_getBoolean("ro.boot.flash.locked")
//console.log(locked)

const sdk = SystemProperties.native_getInt("ro.build.version.sdk")
console.log(sdk)

// console.log(Build.VERSION.require(33))

// const user = BaseEnvironment.getenv("USER")
// const user = Environment.whoami()
// const home = Environment.homedir()
// const tmp = Environment.tmpdir()

// console.log({
//     user,
//     home,
//     tmp
// })

// System.spawn('echo -e "Default \\e[33mYellow"', (res) => {
//   console.log("---: " + res.trim());
// });

//const enabled = BaseSeLinux.isEnabled();
//console.log(enabled)