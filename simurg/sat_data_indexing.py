#!/usr/bin/python3

import time
import h5py 
import pytz
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime, timezone


class SatData:
    
    def __init__(self, filename, filemode = 'r'):
        try:
            self.f = h5py.File(filename, filemode)
        except:
            print("Cannot open the file")
            return
        
        
    def __del__(self):
        #self.f.close()
        pass
        
        
    def get_sites(self):
        return [site for site in self.f]
    
    
    def get_sats(self, site):
        return [sat for sat in self.f[site]]
    
    
    def get_data(self, site, sat, field):
        return self.f[site][sat][field][:]
    
    
    def get_series(self, site, sat, field):
        ts = self.get_data(site, sat, 'timestamp')
        data = self.get_data(site, sat, field)
        return ts, data
    
    
    def get_map(self, time, field):
        result = []
        timestamp = time.timestamp()
        start, end = timestamp, timestamp
        sites = self.get_sites()
        
        for site in sites:
            lat = np.degrees(self.f[site].attrs['lat'])
            lon = np.degrees(self.f[site].attrs['lon'])
            sats = self.get_sats(site)
            
            for sat in sats:                
                timestamps, data = self.get_series(site, sat, field)
                match = np.where((timestamps >= start) & (timestamps <= end))
                data_match = data[match]
                for d in data_match:
                    result.append((d, lon, lat))
        if not result:
            return None
        else:
            return np.array(result)



if __name__ == '__main__':
    plot_map = True
    pth = '2020-05-20.h5'
    if not plot_map:
        timestamps, data = get_series(pth, 'arsk', 'G03', 'dtec_20_60')
        times = [datetime.fromtimestamp(t, pytz.utc) for t in timestamps]
        plt.scatter(times, data)
        plt.xlim(times[0], times[-1])
        plt.show()
    else:
        epoch = datetime(2020, 5, 20, 12, 30, 0, tzinfo=timezone.utc)
        before = time.time()
        
        data = SatData(pth)
        data = data.get_map(epoch, 'dtec_20_60')
        
        print(f'It took {time.time() - before} sec. to retrieve a map')
        val = data[:, 0]
        x = data[:, 1]
        y = data[:, 2]
        plt.scatter(x, y, c=val)
        plt.xlim(-180, 180)
        plt.ylim(-90, 90)
        plt.show()
    


