var lxc = require('.')
var container = lxc('testcontainer')

container.isDefined(function (err, defined) {
  if (err) { return console.log(err.message) }

  if (defined) {
    console.log('the container is defined')
    return start()
  }

  console.log('the container is not defined')

  container.create({
    template: 'download',
    args: ['-d', 'ubuntu', '-r', 'precise', '-a', 'amd64']
  }, function created (err) {
    if (err) { return console.log(err.message) }

    console.log('container created successfully')
    start()
  })
})

function start () {
  container.start({
    useLxcInit: false, // not sure what this is
    args: []
  }, function (err) {
    if (err) { return console.log(err.message) }

    container.getPid(function (err, pid) {
      console.log('the pid is', pid)
    })

    container.getStatus(function (err, status) {
      console.log('the status is', status)
    })
  })
}
