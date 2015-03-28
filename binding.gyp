{
  "targets": [{
    "target_name": "lxc",
    "include_dirs"  : [
      "<!(node -e \"require('nan')\")"
    ],
    "sources": [
      "src/lxc.cc"
    ]
  }]
}
