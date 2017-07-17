import os
import json
PROJECT_DIR = os.getcwd()
with open(PROJECT_DIR + '/socket.json', 'r') as f:
    content = f.read()
    data = json.loads(content)
    SERVER_IP = data['server_ip']
    SERVER_PORT = int(data['server_port'])
    LOCAL_SERVER_IP = data['local_server_ip']
    LISTEN_IP = data['listen_ip']
