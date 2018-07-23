import subprocess
import os


# python solution was devised because some characters in note4 path made sh fail sometimes


remoteTarget='/storage/extSdCard/Android/data/zaza.stable/files'

localSource='/cygdrive/c/Users/thomas/Dropbox/current_zazanim_projects/lassitude'
#localTarget='/cygdrive/c/tmp/zazexport'


def pushframes(files):
    os.chdir(localSource)
    #result=subprocess.run(['adb','pull','-p',remoteSource+'/'+frames[0]])
    #print(result)

    for frame in files :
        print("file to push :"+frame)
        result=subprocess.run(['adb','push',frame,remoteTarget+'/'+frame])
        print(result)



#result=subprocess.run(['adb','shell','ls',remoteSource],stdout=subprocess.PIPE)

#print(result.stdout)

#frames=result.stdout.decode('utf-8').splitlines()

frames=os.listdir(localSource)

print(frames)

#filteredFrames=[]
#filtering empty lines created by parsing return of adb ls
#for frame in frames:
#    if frame:#not empty
#        filteredFrames.append(frame)

#print('filtered frames:')
#print(filteredFrames)

pushframes(frames)
#subprocess.run(['cd',localTarget],stdout=subprocess.PIPE)

#specifying target files fails (maybe because I pass cygwin path )
#result=subprocess.run(['adb','pull','-p',remoteSource+'/'+frames[0],localTarget+'/'+frames[0]])

