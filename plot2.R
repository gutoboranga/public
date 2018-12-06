args = commandArgs(trailingOnly=TRUE)

server1 = read.table(args[1], header = FALSE, sep = "\t", dec = ".")
server2 = read.table(args[2], header = FALSE, sep = "\t", dec = ".")
server3 = read.table(args[3], header = FALSE, sep = "\t", dec = ".")

time = seq(1, 60, by=1)

limit = 100

png("graph.png", width= 1200, height= 1200, units = 'px', res=200)

plot(time, server1[[1]], axes=FALSE, xlab="", ylab="", type="l", col="red", main="Tráfego da rede - 3 conexões", ylim=range(c(0,limit)))

par(new=TRUE)
plot(time, server2[[1]], axes=FALSE, xlab="", ylab="", type="l", col="blue", ylim=range(c(0,limit)))

par(new=TRUE)
plot(time, server3[[1]], axes=FALSE, xlab="", ylab="", type="l", main="", col="green", ylim=range(c(0,limit)))

axis(1,pretty(range(time),10))
axis(2,pretty(seq(1,limit,by=10), 10))
mtext("Tempo (s)",side=1,col="black",line=2.5)
mtext("Taxa de transferência (Mbits)",side=2,col="black",line=2.5)
