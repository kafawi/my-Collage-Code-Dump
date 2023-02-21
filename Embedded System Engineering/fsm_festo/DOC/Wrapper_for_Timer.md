# Wrapper für Timer
#### Timer-Klasse
```
Timer
------------------------------------------
- launchtime : Timestmp  
- timerthread : Thread& 
- currentSpeed : Speed 
- channelRef : Channel& 
- distanceRemeining : unsighned int 
 ------------------------------------------ 
+ Timer(int,Speed) : TimerThread&
+ changedSpeed(Speed) : void
+ getChanel : channel&
```
#### Implementierung
```
// Ziehe geeignet parametrisierten Timer auf
Timer(distance,speed) {
    this.timeToRun = distance / speed;
    this.currentSpeed = speed;
    this.launchtime = currentTime();
    timerThread.launch(this.timeToRun);
}

// Ändert Timerparametrisierung für neue Geschwindigkeit
changeSpeed(speed) {
    timerThread.stop();
    distanceCovered = this.currentSpeed(this.launchtime-currentTime());
    this.timeToRun = (this.distanceRemaining-distanceCovered)/speed;
    timerThread.launch(this.timeToRun);
}
```


S~neu~ = S~alt~ - V~alt~(t~start~ - t)
t~timeout~ = S~neu~ / V~neu~