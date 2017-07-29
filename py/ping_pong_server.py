import thriftpy

pingpong_thrift = thriftpy.load(
    './PingPong.thrift', module_name='pingpong_thrift')

from thriftpy.rpc import make_server


class Dispatcher(object):
    def ping(self):
        return 'pong'


server = make_server(pingpong_thrift.PingPong, Dispatcher(), '0.0.0.0', 6000)
server.serve()
