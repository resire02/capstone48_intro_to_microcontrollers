import os
import subprocess
import tempfile
import shutil

def run_cpplint_on_dir(root_dir):
    for dirpath, _, filenames in os.walk(root_dir):
        for fname in filenames:
            if fname.endswith(('.ino')):
                full_path = os.path.join(dirpath, fname)
                with tempfile.NamedTemporaryFile(suffix='.cpp', delete=False) as tmp:
                    shutil.copyfile(full_path, tmp.name)
                    print(f"Linting (as .cpp): {full_path}")
                    subprocess.run(['cpplint', tmp.name])
                os.unlink(tmp.name)

run_cpplint_on_dir('path/to/your/project')

if __name__ == '__main__':
    run_cpplint_on_dir('C:\\Users\\Gonzalo Allendes\\OneDrive\\Escritorio\\Work & School\\Arizona State University\\capstone48_intro_to_microcontrollers\\deliverables')


