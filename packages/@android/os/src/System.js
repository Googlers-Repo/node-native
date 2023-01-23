import { createRequire } from 'module';
import util from 'util'

const require = createRequire(import.meta.url);
const { getenv, setenv, cmd } = require('/data/data/io.spck/files/android-log/build/Release/android-os.node')

class System {
  static cmd(c, ...data) {
    if (typeof c != 'string') throw new Error('the command beeds to be an string')
    return cmd(util.format(c, ...data)).trim()
  }

  static setenv(name, value, overrid) {
    setenv(String(name), String(value), Number(overrid))
  }

  static getenv(name) {
    if (!name) throw new Error('Undefined name')
    return getenv(String(name))
  }

  static openApp(pkg, act) {
    return this.cmd("am start -n %s/.%s", pkg, act)
  }

  static openFile(file, mimeType) {
    return this.cmd("am start -a android.intent.action.VIEW -d file://%s -t %s", file, mimeType)
  }

  static openUrl(url) {
    var pattern = new RegExp(
      "^(https?:\\/\\/)?" + // protocol
      "((([a-z\\d]([a-z\\d-]*[a-z\\d])*)\\.)+[a-z]{2,}|" + // domain name
      "((\\d{1,3}\\.){3}\\d{1,3}))" + // OR ip (v4) address
      "(\\:\\d+)?(\\/[-a-z\\d%_.~+]*)*" + // port and path
      "(\\?[;&a-z\\d%_.~+=-]*)?" + // query string
      "(\\#[-a-z\\d_]*)?$",
      "i"
    ); // fragment locator
    if (!pattern.test(url)) {
      throw new Error(`'${url}' is not a valid url!`)
    } else {
      return this.cmd('am start -a android.intent.action.VIEW -d %s', url)
    }
  }

  static notify(id, title, message, ...data) {
    if (typeof id != "number") throw new Error("The 'id' should be an number")
    if (typeof title != "string") throw new Error("The 'title' should be an string")
    if (typeof message != "string") throw new Error("The 'message' should be an string")
    return this.cmd(`su -lp 2000 -c "cmd notification post -S bigtext -t '${title}' '${id}' '${util.format(message, ...data)}'"`)
  }
}

export {System}