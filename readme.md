# Sensor Bridge Client

This is the client that connects to the 
[Sensor Bridge board](https://github.com/sensorlab030/sensorbridge). It
collects data via the serial port from the sensors connected to the board and 
allows the data to be recorded to CSV or JSON files, or served via websockets.

The application is written in C++ using the Qt 5.8.0

## Protocol

The protocol to transport the sensor data over the serial connection can be 
found in the [Sensor Bridge readme](https://github.com/sensorlab030/sensorbridge/blob/master/readme.md)

## License

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.



