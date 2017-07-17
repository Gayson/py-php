import thriftpy
from thriftpy.rpc import make_client
import setting

data_service_thrift = thriftpy.load(setting.PROJECT_DIR + '/idls/DataService.thrift', module_name='data_service_thrift')

client = make_client(data_service_thrift.Calculator, '127.0.0.1', 6000)

print client.ping()
print client.add(4, 5)

work = data_service_thrift.Work()
work.op = data_service_thrift.Operation.DIVIDE
work.num1 = 6
work.num2 = 3

log = data_service_thrift.shared.SharedStruct()

log.key = 3
log.value = 'hh'

print client.calculate(1, work)

work.num2 = 0
try:
    print client.calculate(2, work)
except Exception as e:
    print e.message

work.op = 6
try:
    print client.calculate(3, work)
except Exception as e:
    print e.message

try:
    log = client.getStruct(1)
    print log.value
except Exception as e:
    print e.message
