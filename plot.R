args = commandArgs(trailingOnly=TRUE)

server1 = read.table(args[1], header = FALSE, sep = "\t", dec = ".")
server2 = read.table(args[2], header = FALSE, sep = "\t", dec = ".")

time = seq(1, 120, by=1)

png("graph.png", width= 1200, height= 1200, units = 'px', res=200)

plot(time, server2[[1]], axes=FALSE, xlab="", ylab="", type="l", col="red", main="Tráfego com 2 conexões")

par(new=TRUE)

plot(time, server1[[1]], axes=FALSE, xlab="", ylab="", type="l", col="blue")

axis(1,pretty(range(time),10))
axis(2,pretty(seq(1,100,by=20)))
mtext("Segundos",side=1,col="black",line=2.5)
mtext("Mbits",side=2,col="black",line=2.5)
