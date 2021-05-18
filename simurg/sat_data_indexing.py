#!/usr/bin/python3

import time
import h5py 
import pytz
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime, timezone
import pathlib


class SatData:
    
    def __init__(self, filename, filemode = 'r'):
        self.f = h5py.File(filename, filemode)
        self.filename = filename
        
        
    def __del__(self):
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
        dir_path = f"./data_map/{self.filename[:-3]}/"
        filename = f'{time}-{field}'
        p = pathlib.Path(dir_path)

        if not p.is_dir():
            p.mkdir(parents=True)
            
        p = pathlib.Path(dir_path + filename)
        if p.is_file(): # open and read data
            data = np.fromfile(p)
            data, shape = data[:-2], tuple(map(int, data[-2:]))
            return data, shape
        
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
                for d in data[match]:
                    result.append((d, lon, lat))
        if not result:
            return None
        else:
            result = np.array(result)
            result = np.array(list(result.flatten()) + list(result.shape))
            result.tofile(p)
            return result
        # finish with shape
    

if __name__ == '__main__':
    plot_map = True
    pth = '2020-05-20.h5'
    #pth = '2018-08-26.h5'
        
    if not plot_map:
        timestamps, data = get_series(pth, 'arsk', 'G03', 'dtec_20_60')
        times = [datetime.fromtimestamp(t, pytz.utc) for t in timestamps]
        plt.scatter(times, data)
        plt.xlim(times[0], times[-1])
        plt.show()
    else:        
        epoch = datetime(2020, 5, 20, 12, 30, 0, tzinfo=timezone.utc)
        before = time.time()
                        
        try:
            data = SatData(pth)
            data, shape = data.get_map(epoch, 'dtec_20_60')
            data = data.reshape(shape)
        except IOError:
            print("Cannot open file")
            exit(1)
        except:
            print("Undefined error")
            exit(2)
        
        print(f'It took {time.time() - before} sec. to retrieve a map')
        val = data[:, 0]
        x = data[:, 1]
        y = data[:, 2]
        plt.scatter(x, y, c=val)
        plt.xlim(-180, 180)
        plt.ylim(-90, 90)
        plt.show()
    


