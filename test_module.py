import os
import sys
import numpy as np
import shutil
import argparse
#from ase import io
#from tqdm import tqdm
#from MACE_lib import MACE
import pickle
#import plotly.graph_objects as go
#from plotly.subplots import make_subplots
#from sklearn.metrics import mean_squared_error
#from math import sqrt

'''
python random_struc_gen.py random --stoichiometry='1 3' --species='Al F' --cluster_size='2' --sample_size=2
python random_struc_gen.py dft_opt_mace --target_str='collect_opt.xyz'
'''

class RANDOM_CLUSTER_GEN:

    def __init__(self): #, args):
        #self.args = args
        self.ucl_id = 'uccatka'
        self.job_time = '4:00:00'
        self.job_name = 'test'
        self.memory = '1'
        self.cpu_core = '40'  # for Young 40 core = 1 node
        self.payment = 'Gold'
        self.budgets = 'UCL_chemM_Woodley'
        self.path_binary = '/home/uccatka/software/fhi-aims.221103/build/aims.221103.scalapack.mpi.x'
        self.path_fhiaims_species = '/home/uccatka/software/fhi-aims.221103/species_defaults/defaults_2020/light'
        self.species = 'Al F'
        self.stoi = '1 3'
        self.cluster_size = 3
        self.sample_size = 2
        
          

    def random_init(self, sim_box_size):
        #self.species = self.args.species.split()
        #self.species = species

        self.cat = self.species[0]
        self.an = self.species[1]

        #self.stoi = self.args.stoichiometry.split()
        self.stoi = self.stoi.split()
        self.cat_in_mono = int(self.stoi[0])
        self.an_in_mono = int(self.stoi[1])

        #self.cluster_size = int(self.args.cluster_size)

        self.no_of_cat = self.cat_in_mono * self.cluster_size
        self.no_of_an = self.an_in_mono * self.cluster_size
        self.no_of_tot = self.no_of_cat + self.no_of_an

        self.ID_cat = [self.cat] * self.no_of_cat
        self.ID_an = [self.an] * self.no_of_an
        self.ID = np.array(self.ID_cat + self.ID_an)

        #self.sample_size = int(self.args.sample_size)

        self.sim_box_size = round(float(sim_box_size), 2)
        self.collide = 1.5


    def RAND_CRUDE_COORD(self):
        place_hold = np.zeros((1, 3))
        for i in range(self.no_of_tot):
            crude_atom_coord = np.random.uniform(low=-self.sim_box_size, high=self.sim_box_size, size=(1,3))
            place_hold = np.append(place_hold, crude_atom_coord, axis=0)
        crude_coord = place_hold[1:]
        return crude_coord


    def ADJUST(self, crude_coord):
        for i in range(len(crude_coord)):
            for j in range(len(crude_coord)):
                if i != j:
                    dist = np.round(np.linalg.norm(crude_coord[i] - crude_coord[j]), 9)
                    while dist < self.collide:
                        collision = True
                        while collision:
                            collision = False
                            crude_atom_coord = np.random.uniform(low=-self.sim_box_size, high=self.sim_box_size, size=(1,3))
                            for k in range(len(crude_coord)):
                                if k != i and np.round(np.linalg.norm(crude_atom_coord - crude_coord[k]), 9) < self.collide:
                                    collision = True
                                    break
                        matching = np.where(np.all(crude_coord == crude_coord[i], axis=1))[0]
                        crude_coord[matching] = crude_atom_coord[0]
                        dist = np.round(np.linalg.norm(crude_atom_coord - crude_coord[j]), 9)
        random_struc = crude_coord
        random_struc = np.round(random_struc, 9)
        del crude_coord
        return random_struc


    def XYZ_CONTENT(self, random_struc):
        dummy_force = np.zeros((self.no_of_tot, 3))
        cluster = np.c_[self.ID, random_struc, dummy_force]
        return cluster


    def W_XYZ(self, cluster, label):
        with open(f"sampling/{label}/{label}.xyz", 'w') as f:
            f.write(f"{self.no_of_tot}\n")
            f.write('Lattice="0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0" ')
            f.write('Properties=species:S:1:pos:R:3:force:R:3')
            f.write('energy=0.00000 pbc="F F F"\n')
            for j in cluster.tolist():
                f.write('\t'.join(j))
                f.write('\n')
        return None 


    def W_geometry_in(self, work_dir, random_struc, ID, label): 
        #if isinstance(random_struc, np.ndarray):
        no_atoms = np.shape(random_struc)[0] 
        first_column = np.reshape(np.array(['atom'] * no_atoms), (no_atoms, -1))
        try:
            contents = np.c_[first_column, random_struc, ID].tolist()
        except:
            contents = np.c_[first_column, random_struc, ID].tolist()
        with open(f'{work_dir}/{label}/geometry.in', 'w') as f:
            for row in contents:
                line = "{:<10}{:<20}{:<20}{:<15}{:<10}".format(*row)
                f.write(line + '\n')
        #else:
        #    for shape, arrays in random_struc.items():
        #        no_atoms = shape[0]
        #        first_column = np.reshape(np.array(['atom'] * no_atoms), (no_atoms, -1))
        #        contents = np.c_[first_column, arrays, ID, label].tolist()
        #        #with open(f'{work_dir}/{label}/geometry.in', 'w') as f:
        #        #    for row in contents:
        #        #        line = "{:<10}{:<20}{:<20}{:<15}{:<10}".format(*row)
        #        #        f.write(line + '\n')

        return contents


    def W_GULP(self, cluster, label):
        #print(f"sampling/{label}/gulp_{label}.gin")
        with open(f"sampling/{label}/gulp_{label}.gin", 'w') as f:
            f.write('opti conp rfo phonon noden\n')
            f.write('cartesian\n')
            #for k in cluster[i].tolist():
            cluster = cluster.tolist()
            for i in cluster: 
                i = i[:-3]
                i.insert(1, 'core')
                f.write('    '.join(i))
                f.write('\n')
            f.write('species\n')
            f.write('Al core  3.00\n')
            f.write('F  core  0.59\n')
            f.write('F  shel -1.59\n')
            f.write('buck\n')
            f.write('Al  core  F   shel  3760.000831  0.222000   0.00000 0.0 10.0\n')
            f.write('buck4\n')
            f.write('F   shel  F   shel  1127.7 0.2753 15.83 2.0 2.79 3.031 12.0\n')
            f.write('spring\n')
            f.write('F 20.77\n')
            f.write('xtol opt   6.000000\n')
            f.write('gtol opt   5.000000\n')
            f.write('ftol opt   8.000000\n')
            #f.write('switch rfo 0.4\n')
            f.write('maxcyc 10000\n')
            f.write(f'output xyz sampling/{label}/out_{label}')
        return None                   


    def GULP_SUBMIT(self, path):
        parent = f"sampling/{path}"
        gulp_input = [x for x in os.listdir(f'sampling/{path}') if 'gin' in x][0]
        gulp_input = gulp_input.split('.')[0] 
        gulp_input_pth = f"sampling/{path}/{gulp_input}"

        gulp_output = gulp_input.split('.')[0] + '.gout'
        gulp_output_pth = f"sampling/{path}/{gulp_output}"

        os.system(f"/home/uccatka/software/gulp-5.1/Src/gulp 'sampling/{path}/{gulp_input}' > {gulp_output_pth} 2>&1")

        with open(gulp_output_pth, 'r') as f:
            output = f.read()
        if "Program terminated by processor" in output:
            shutil.rmtree(f'sampling/{path}')
        else:
            with open(f'{parent}/out_{path}.xyz', 'r') as f:
                E = f.readlines()[1].split()[2]
                E_path = path
            return E_path, E 


    def make_sp_control(self, path, ID, charge=0.0):
        ''' Write {control.in} file '''
        basis_set_files = [os.path.join(self.path_fhiaims_species, x) for x in os.listdir(self.path_fhiaims_species)]
        basis_set_all = [x.split('_')[1] for x in os.listdir(self.path_fhiaims_species)]
        basis_set_index = [basis_set_all.index(x) for x in basis_set_all if x in ID]

        path = os.path.join(path, 'control.in')
        with open(path, 'a') as f:
            f.write("#\n")
            f.write("xc                 pbesol\n")
            f.write("spin               none\n")
            f.write("relativistic       atomic_zora scalar\n")
            f.write(f"charge             {charge}\n\n")
            f.write("#  SCF convergence\n")
            f.write("occupation_type    gaussian 0.01\n")
            f.write("mixer              pulay\n")
            f.write("n_max_pulay        10\n")
            f.write("charge_mix_param   0.5\n")
            f.write("sc_accuracy_rho    1E-5\n")
            f.write("sc_accuracy_eev    1E-3\n")
            f.write("sc_accuracy_etot   1E-6\n")
            f.write("sc_accuracy_forces 1E-4\n")
            f.write("sc_iter_limit      1500\n")
            f.write("#  Relaxation\n\n")
            #f.write("relax_geometry   bfgs 1.e-3\n")
            for i in basis_set_index:
                with open(basis_set_files[i], 'r') as ff:
                    lines = ff.read()
                f.write(lines)
                f.write('\n')
        return None


    def make_job_submit(self, path):
        ''' Write 'submit.sh' job script for SGE system '''
        _, last_part = os.path.split(os.getcwd())
        _, second_last_part = os.path.split(os.path.dirname(os.getcwd()))
        _, third_last_part = os.path.split(os.path.dirname(os.path.dirname(os.getcwd())))

        # Combine the last two parts
        last_two_parts = f"{third_last_part}_{last_part}"

        path = os.path.join(path, 'submit.sh')
        with open(path, 'a') as f:
            f.write("#!/bin/bash -l\n")
            f.write('\n')
            f.write('#This job script is for Young')
            f.write("#$ -S /bin/bash\n")
            f.write(f"#$ -l h_rt={self.job_time}\n")
            f.write(f"#$ -l mem={self.memory}G\n")
            f.write(f"#$ -N p{last_two_parts}\n")
            f.write(f"#$ -pe mpi {self.cpu_core}\n")
            f.write("#$ -cwd\n")
            f.write("\n")
            f.write(f"#$ -P {self.payment}\n")
            f.write(f"#$ -A {self.budgets}\n")
            f.write("\n")
            f.write("module load gerun\n")
            f.write("module load userscripts\n")
            f.write("module unload -f compilers mpi gcc-libs\n")
            f.write("module load gcc-libs/4.9.2\n")
            f.write("module unload -f compilers mpi\n")
            f.write("module load beta-modules\n")
            f.write("module load openblas/0.3.7-serial/gnu-4.9.2\n")
            f.write("module load compilers/intel/2019/update5\n")
            f.write("module load mpi/intel/2018/update3/intel\n")
            f.write("\n")
            f.write("####$ -m e\n")
            f.write(f"####$ -M {self.ucl_id}@ucl.ac.uk\n")
            f.write("\n")

            f.write("# Loop through all directories\n")
            f.write("for dir in *; do\n")
            f.write('  cd "$dir"\n')
            f.write(f"  gerun {self.path_binary} > aims.out 2> aims.err\n")
            f.write("  cd ..\n")
            f.write("done\n")

    def convert_ensemble_cluster_xyz(self, target):
        ensemble = io.read(target, index=":")
        no_atoms = np.shape(ensemble[0].get_positions())[0]
        atom_label = np.reshape(['atom'] * no_atoms, (no_atoms, 1))

        structures = []
        all_labels = []
        for i in ensemble:
            geometry = i.get_positions()
            labels = i.get_chemical_symbols()
            structures.append(geometry) 
            all_labels.append(labels)

        return structures, all_labels    


    def separate_by_shape(self, arr_list):
        shape_dict = {}
        for arr in arr_list:
            shape = arr.shape
            if shape not in shape_dict:
                shape_dict[shape] = []
            shape_dict[shape].append(arr)
         
        return shape_dict

def random_gen():
    random = RANDOM_CLUSTER_GEN()
    #if args.mode == 'random':
    species = random.species.split()
    stoi = random.stoi.split()
    cluster_size = random.cluster_size
    sample_size = random.sample_size
    sim_box_size = 3.0
    #random = random_struc_gen.RANDOM_CLUSTER_GEN(args)
    random.random_init(sim_box_size)

    cat_mono = int(random.stoi[0])
    an_mono = int(random.stoi[1])
    no_of_cat = cat_mono * cluster_size
    no_of_an = an_mono * cluster_size
    no_of_tot = no_of_cat + no_of_an

    step_cnt = 1
    order = 0
    storage = np.zeros((no_of_tot, 7))
    saddle_path_holder = {}
    E_path_holder = {}
    while step_cnt <= int(sample_size):
        #print(step_cnt)
        crude_coord = random.RAND_CRUDE_COORD()
        random_struc = random.ADJUST(crude_coord)
        cluster = random.XYZ_CONTENT(random_struc)
        storage = np.append(storage, cluster, axis=0)
        order += 1
        dest = order
        work_dir = 'sampling'
        if work_dir not in os.listdir('./'):
            os.mkdir(work_dir)

        label = str(step_cnt).zfill(len(str(sample_size)))
        os.mkdir(f"{work_dir}/{label}")
        random.W_geometry_in(work_dir, random_struc, random.ID, label)
        #random.make_sp_control(f'./{work_dir}/{label}', random.ID)
        break
    step_cnt += 1


if __name__ == '__main__':
	random_gen() 
#if __name__ == '__main__':
#    random = RANDOM_CLUSTER_GEN()
#    random.random_gen()
#    #parser = argparse.ArgumentParser(description='Generate random structure of nanoclusters.')
#    #subparsers = parser.add_subparsers(dest='mode')
#
#    ## Random structure generation parser
#    #random_parser = subparsers.add_parser('random', help='Perform random structure generation')
#    ##random_parser.add_argument('--species', type=str, help='Species involved in the cluster')
#    ##random_parser.add_argument('--stoichiometry', type=str, help='Stoichiometry in format "1 3"')
#    ##random_parser.add_argument('--cluster_size', type=int, help='Size of the cluster')
#    ##random_parser.add_argument('--sample_size', type=int, help='Number of samples')
#
#    ## DFT optimization parser
#    #dft_parser = subparsers.add_parser('dft_opt_mace', help='DFT optimize the MACE optimized ensembles')
#    #dft_parser.add_argument('--target_str', type=str, help='target MACE optimized ensemble structure')
#
#    ## Compare DFT opt MACE and MACE opt
#    #comp_parser = subparsers.add_parser('compare', help='DFT opt MACE VS MACE opt')
#    #comp_parser.add_argument('--dft_opt_mace', type=str, help='target DFT optimized MACE structure')
#    #comp_parser.add_argument('--mace_opt', type=str, help='MACE optimized structure')
#    #
#    #args = parser.parse_args()
#
#    #random = RANDOM_CLUSTER_GEN(args)
#    #if args.mode == 'random':
#    #species = random.species.split()
#    #stoi = random.stoi.split()
#    #cluster_size = random.cluster_size
#    #sample_size = random.sample_size
#    #sim_box_size = 3.0
#    ##random = random_struc_gen.RANDOM_CLUSTER_GEN(args)
#    #random.random_init(sim_box_size)
#
#    #cat_mono = int(random.stoi[0])
#    #an_mono = int(random.stoi[1])
#    #no_of_cat = cat_mono * cluster_size
#    #no_of_an = an_mono * cluster_size
#    #no_of_tot = no_of_cat + no_of_an
#
#    #step_cnt = 1
#    #order = 0
#    #storage = np.zeros((no_of_tot, 7))
#    #saddle_path_holder = {}
#    #E_path_holder = {}
#    #while step_cnt <= int(sample_size):
#    #    print(step_cnt)
#    #    crude_coord = random.RAND_CRUDE_COORD()
#    #    random_struc = random.ADJUST(crude_coord)
#    #    cluster = random.XYZ_CONTENT(random_struc)
#    #    storage = np.append(storage, cluster, axis=0)
#    #    order += 1
#    #    dest = order
#    #    work_dir = 'sampling'
#    #    if work_dir not in os.listdir('./'):
#    #        os.mkdir(work_dir)
#
#    #    label = str(step_cnt).zfill(len(str(sample_size)))
#    #    os.mkdir(f"{work_dir}/{label}")
#    #    random.W_geometry_in(work_dir, random_struc, random.ID, label)
#    #    #random.make_sp_control(f'./{work_dir}/{label}', random.ID)
#
#    #    step_cnt += 1
#
#    ##random.make_job_submit(f'./{work_dir}')

