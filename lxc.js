var binding = require('bindings')('lxc.node').lxc
var assert = require('assert')

function Container (name) {
  if (!(this instanceof Container)) {
    return new Container(name)
  }

  assert(name, 'missing name')

  this.binding = binding(name)
}

Container.prototype.isDefined = function (cb) {
  this.binding.isDefined(cb)
}

Container.prototype.getPid = function (cb) {
  this.binding.getPid(cb)
}

Container.prototype.getStatus = function (cb) {
  this.binding.getStatus(cb)
}

Container.prototype.start = function (opts, cb) {
  this.binding.start(opts, cb)
}

Container.prototype.create = function (opts, cb) {
  this.binding.create(opts, cb)
}

module.exports = Container
