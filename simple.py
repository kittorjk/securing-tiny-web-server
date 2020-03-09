import telnetlib

tn = telnetlib.Telnet("localhost", 8000)
data = "GET /"

tn.write(data + "\r")
tn.write("\n")

print tn.read_all()
