const { System, SystemProperties, Build, Environment } = require(".")

// console.log(System.uname())

// Should throw error
// System.cmd("cmd battery reset -f")

// const locked = SystemProperties.get("ro.boot.flash.locked")

// console.log(Build.LOCKED)


// console.log(Build.VERSION.require(33))

// const user = BaseEnvironment.getenv("USER")
const user = Environment.whoami()
const home = Environment.homedir()
const tmp = Environment.tmpdir()

console.log({
    user,
    home,
    tmp
})