import thriftpy

pingpong_thrift = thriftpy.load('./PingPong.thrift', module_name='pingpong_thrift')

from thriftpy.rpc import make_client

client = make_client(pingpong_thrift.PingPong, '115.159.222.144', 6000)
print client.ping()
