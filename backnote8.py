import subprocess
import os
#remoteSource='/storage/9C33-6BBD/Android/data/zaza.dev205/files'
remoteSource='/storage/extSdCard/Android/data/zaza.stable/files'

#localTarget='/cygdrive/c/Users/thomas/Dropbox/current_zazanim_projects/mechagirl/prologue2'
localTarget='/cygdrive/c/tmp/zazexport'
#localTarget='/cygdrive/c/Users/thomas/Dropbox/current_zazanim_projects/corposhow'
#localTarget='/cygdrive/c/Users/thomas/andro/ws/zazadev205/win32/current'
def pullframes(files):
    os.chdir(localTarget)
    #result=subprocess.run(['adb','pull','-p',remoteSource+'/'+frames[0]])
    #print(result)

    for frame in files :
        print("file to pull :"+frame)
        result=subprocess.run(['adb','pull',remoteSource+'/'+frame])
        print(result)



result=subprocess.run(['adb','shell','ls',remoteSource],stdout=subprocess.PIPE)

print(result.stdout)

frames=result.stdout.decode('utf-8').splitlines()

print(frames)

filteredFrames=[]
#filtering empty lines created by parsing return of adb ls
for frame in frames:
    if frame:#not empty
        filteredFrames.append(frame)

print('filtered frames:')
print(filteredFrames)

pullframes(filteredFrames)
#subprocess.run(['cd',localTarget],stdout=subprocess.PIPE)

#specifying target files fails (maybe because I pass cygwin path )
#result=subprocess.run(['adb','pull','-p',remoteSource+'/'+frames[0],localTarget+'/'+frames[0]])

