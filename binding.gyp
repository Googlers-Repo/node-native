{
	"targets": [
		{
			"target_name": "android-os",
			"include_dirs": [
				"<!(sh -c \"echo \$PREFIX/include\")",
        "<!(node -p \"require('node-addon-api').include\")"
      ],
			"sources": [
      	"packages/@android/os/native/system/system.cpp",
      	"packages/@android/os/native/properties/properties.cpp",
      	"packages/@android/os/native/main.cpp"
      ],
      "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    },
		{
			"target_name": "android-util",
			"include_dirs": [
				"<!(sh -c \"echo \$PREFIX/include\")",
        "<!(node -p \"require('node-addon-api').include\")"
      ],
      "libraries": [
        "-llog"
      ],
      "sources": [
      	"packages/@android/util/native/log/log.cpp",
      	"packages/@android/util/native/main.cpp",
      ],
      "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    },
		{
			"target_name": "magisk",
			"include_dirs": [
				"<!(sh -c \"echo \$PREFIX/include\")",
				"<!(sh -c \"echo \$PWD/packages/magisk/native/include\")",
				"<!(sh -c \"echo \$PWD/packages/magisk/native/base/include\")",
        "<!(node -p \"require('node-addon-api').include\")"
      ],
      "libraries": [
        "-llog"
      ],
      "sources": [
      	"packages/@android/util/native/log/log.cpp",
      	"packages/@android/util/native/main.cpp",
      ],
      "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}