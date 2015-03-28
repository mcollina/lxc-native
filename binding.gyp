{
  "targets": [{
    "target_name": "lxc",
    "include_dirs"  : [
      "<!(node -e \"require('nan')\")"
    ],
    "link_settings": {
      "libraries": [
        "-llxc",
      ]
    },
    "sources": [
      "src/lxc.cc",
      "src/container.cc"
    ]
  }]
}
