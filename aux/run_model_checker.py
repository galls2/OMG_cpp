import os
import signal
import sys
import filecmp
import time
import subprocess
from subprocess import STDOUT, check_output
from subprocess import Popen, PIPE, TimeoutExpired
from time import monotonic as timer

PATH_TO_MODELS = '~/Desktop/OMG_cpp/resources'

class ResultWriter:
    def __init__(self, model_names, timeout):
        self._results = {model_name : dict() for model_name in model_names}
        self._timeout = timeout
        
    def add_data(self, model_name, prop_idx, time_took):
        if model_name not in self._results.keys():
            raise Exception('Unknown model!')

        self._results[model_name][prop_idx] = time_took

    def export_data(self, path_to_export):
        with open(path_to_export, 'w') as f:
            for model_name in self._results:
                f.write(model_name + ":\n")
                model_results = self._results[model_name]
                for prop_idx in model_results.keys():
                    f.write(str(prop_idx) + " : " + str(model_results[prop_idx]) +"\n")
            f.write(f"Timeout: {self._timeout}")


def run_with_timeout(cmd, timeout_):
    try:
        start_time = time.time()    
#        cmd_success_output = subprocess.check_output(cmd, shell=True, timeout=timeout, stderr=subprocess.STDOUT).decode()
        start = timer()
        with Popen(cmd, shell=True, stdout=PIPE, stderr=PIPE, preexec_fn=os.setsid) as process:
            try:
                res = process.communicate(timeout=timeout_)
                output = res[0].decode() + res[1].decode()
            except TimeoutExpired:
                os.killpg(process.pid, signal.SIGINT) # send signal to the process group
                res = process.communicate()
                output = res[0].decode() + res[1].decode()
                print("Timeout!")
                return output, "Timeout!"
        end_time = time.time()
        return output, end_time - start_time

    except:
        print("?????HUHHUUH")
        return 'UNKNOWN_ERROR', NONE

def run_iimc(path_to_iimc, aig_file, ctl_file, prop_idx, timeout):
    cmd = f"{path_to_iimc} {PATH_TO_MODELS}/{aig_file} --ctl {PATH_TO_MODELS}/{ctl_file} --pi {prop_idx}"
    run_output, time_took = run_with_timeout(cmd, timeout)
    print(f'Time took: {time_took}')
    return run_output, time_took

def run_model(timeout, aig_file, path_to_iimc, path_to_omg, res_writer):
    model_name = aig_file[:-4]
    print(f"Checking {model_name}")
    ctl_file = model_name + '.ctl'
    ctl_loc = f"/home/galls2/Desktop/OMG_cpp/resources/{ctl_file}"
#    print(ctl_loc)
    if not os.path.isfile(ctl_loc):
        return 
    prop_idx = 0
    while True:
        print(f"Prop {prop_idx}... ", end=' ')
        output, time_took = run_iimc(path_to_iimc, aig_file, ctl_file, prop_idx, timeout)
        if 'Property index out of range' in output:
          print(" doesn't exist!")
          break

        print(f"done!")
        print('------------------')          
        
        res_writer.add_data(model_name, prop_idx, time_took)
        prop_idx += 1
        if prop_idx > 500:
            print("Stopped after 500 props")
            break


def run_model_checkers(timeout, models_to_run, path_to_iimc, path_to_omg):
    aig_files = []

    with open(models_to_run, 'r') as models_file:
        aig_files = [x.replace('\n','') for x in models_file.readlines()]

    model_names = [x.replace('.aig','') for x in aig_files]
    res_writer = ResultWriter(model_names, timeout)
  
    for aig_file in aig_files:
        run_model(timeout, aig_file, path_to_iimc, path_to_omg, res_writer)

    
    res_writer.export_data('iimc_results.txt')

if __name__ == '__main__':
    if len(sys.argv) != 5:
        print('Usage: python run_model_checkers.py <models_to_run.txt> <path_to_iimc> <path_to_omg> <timeout_in_seconds>')
    else:
        models_to_run = sys.argv[1]
        path_to_iimc = sys.argv[2]
        path_to_omg = sys.argv[3]
        timeout = int(sys.argv[4])
        run_model_checkers(timeout, models_to_run, path_to_iimc, path_to_omg)
