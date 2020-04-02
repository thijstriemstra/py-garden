# Copyright (c) 2018-2020 Collab
# See LICENSE for details.

import time

from machine import Pin, ADC

from pygarden.lib import logging


__all__ = ['SoilSensor']


logger = logging.getLogger(__name__)

MAX_VALUE = 3171


class SoilSensor(object):
    """
    Soil moisture sensor, or hygrometer, is used to determine the humidity of
    soil.

    See:

    - http://docs.dfrobot.com.cn/upycraft/4.1.4%20analogRead.py.html
    - https://diyprojects.io/micropython-project-several-ds18b20-probes-publish-measurements-domoticz/
    - http://randomnerdtutorials.com/guide-for-soil-moisture-sensor-yl-69-or-hl-69-with-the-arduino/
    """
    prev = 0

    def __init__(self, label='1', pin_nr=32, topic='soil/{}/percentage'):
        self.label = label
        self.pin_nr = pin_nr
        self.topic = topic

        self.pin = ADC(Pin(pin_nr))
        self.pin.atten(self.pin.ATTN_11DB)  # Full Scale: 3.3v
        self.pin.width(self.pin.WIDTH_12BIT)  # Set the 12-bit data width

    def read(self):
        return self.pin.read()

    def publish(self, client):
        sensorValue = self.read()
        msg = str(sensorValue / (MAX_VALUE / 100))
        logger.debug("* Soil {}: {}% on topic '{}'".format(
            self.label, msg, self.topic))
        client.publish(self.topic, msg)

    def start(self):
        while True:
            # read the input
            sensorValue = self.read()
            if sensorValue != self.prev:
                perc = sensorValue / (MAX_VALUE / 100)
                logger.debug('{} ({}%)'.format(sensorValue, perc))
                self.prev = sensorValue
                time.sleep(0.1)

    def destroy(self):
        self.pin.deinit()

    def __repr__(self, *args, **kwargs):
        return 'SoilSensor [label={} pin={}]'.format(
            self.label, self.pin_nr)
