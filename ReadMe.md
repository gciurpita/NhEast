### RR East Interlock - Bill Lupoli's New Haven

<a href=http://www.pacificsouthern.org/Members/BillLupoli/Images/nhPanel.png>
<img width=400 align=right
  src=http://www.pacificsouthern.org/Members/BillLupoli/Images/nhPanel.png></a>

The east interlock panel control turnouts at the east end
of New Haven station.
There is a separate panel at the west end of the station.
The interlock panel aligns turnouts on the route between two buttons
pressed on the panel.

The code for the Arduino based controller
was originally written by Geoff Green.
Changes have been made to correct and add aditional routes.

<!-- -------------------------------------------  -------------------------- -->
<h4> Hardware </h4>

<img height=250 align=right
  src=http://www.pacificsouthern.org/Members/BillLupoli/Images/IMG_1329.JPG>

The hardware is composed of
<li> Model Railroad Control Systems (MRCS)
<a href=https://www.modelrailroadcontrolsystems.com/iox16-version-2-2-16-line-i-o-expander/>
IOX16 I2C I/O Expander</a>
<li> MRCS 
<a href=https://www.modelrailroadcontrolsystems.com/csnk-version-2-high-current-adapter-for-cpnode-iox16-iox32/>
High Current Adapter</a>
<li> custom latching relay board that powers Tortoise switch machines

<img width=150
  src=http://www.pacificsouthern.org/Members/BillLupoli/Images/IMG_1330.JPG>
<img width=150
  src=http://www.pacificsouthern.org/Members/BillLupoli/Images/IMG_1333.JPG>
<img width=150
  src=http://www.pacificsouthern.org/Members/BillLupoli/Images/IMG_1332.JPG>

<!-- -------------------------------------------  -------------------------- -->
<h4> Routes </h4>

Unlike the
<a href=https://www.modelrailroadcontrolsystems.com/csnk-version-2-high-current-adapter-for-cpnode-iox16-iox32/>
west interlock</a>
which is table driven,
the east interlock code
describes routes with explict coding

<blockquote><pre>
  else if(bB7 && bD4)   //B7 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bB7 && bD4)
      {
        pulse(s8N);
        pulse(s12R);
        pulse(s16N);
        pulse(s17N);
        pulse(s23N);
        pulse(s24N);
        pulse(s25N);
        routeSet = true;
      }
    }
  }
</blockquote></pre>
