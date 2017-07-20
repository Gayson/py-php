import thriftpy
from thriftpy.rpc import make_server
import setting

data_service_thrift = thriftpy.load(
    setting.PROJECT_DIR + '/idls/DataService.thrift',
    module_name='data_service_thrift')


class Dispatcher(object):
    def __init__(self):
        self.logs = {}

    def ping(self):
        print 'ping request'
        return 'pong'

    def add(self, num1, num2):
        return num1 + num2

    def calculate(self, logid, w):
        if w.op == data_service_thrift.Operation.ADD:
            val = w.num1 + w.num2
        elif w.op == data_service_thrift.Operation.SUBTRACT:
            val = w.num1 - w.num2
        elif w.op == data_service_thrift.Operation.MULTIPLY:
            val = w.num1 * w.num2
        elif w.op == data_service_thrift.Operation.DIVIDE:
            if w.num2 == 0:
                io = data_service_thrift.InvalidOperation()
                io.whatOp = w.op
                io.why = 'cannot divide by 0'
                raise io
            val = w.num1 / w.num2
        else:
            io = data_service_thrift.InvalidOperation()
            io.whatOp = w.op
            io.why = 'Invalid Operation'
            raise io
        log = data_service_thrift.shared.SharedStruct()
        log.key = logid
        log.value = str(val)

        self.logs[logid] = log
        return val

    def zip(self):
        print 'remote zip'

    def getStruct(self, key):
        if key in self.logs.keys():
            return self.logs[key]
        else:
            return None


server = make_server(data_service_thrift.Calculator,
                     Dispatcher(), setting.LISTEN_IP, setting.SERVER_PORT)
server.serve()
