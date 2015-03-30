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
    "flags": "-fpermissive",
    "sources": [
      "src/lxc.cc",
      "src/container.cc",
      "src/is_defined_worker.cc",
      "src/create_worker.cc"
    ]
  }]
}
