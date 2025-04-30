import os
import subprocess
import tempfile
import shutil

def run_cpplint_on_ino_files(root_dir, output_path='./project/tests/cpplint_report.txt'):
    exclude_dirs = []

    with open(output_path, 'w') as report:
        for dirpath, _, filenames in os.walk(root_dir):
            for fname in filenames:
                if fname.startswith('Base_Example'):
                    continue
                if fname.endswith('.ino'):
                    full_path = os.path.join(dirpath, fname)

                    # Create a temp .cpp copy
                    with tempfile.NamedTemporaryFile(suffix='.cpp', delete=False) as tmp:
                        tmp_path = tmp.name
                    shutil.copyfile(full_path, tmp_path)

                    # Run cpplint
                    label = f"Linting {full_path} (as .cpp)\n"
                    result = subprocess.run(['cpplint', tmp_path], capture_output=True, text=True)

                    # Write results to .txt file
                    report.write(label)
                    report.write(result.stdout)
                    report.write(result.stderr)
                    report.write("\n" + "="*80 + "\n")

                    # Delete temp file
                    os.unlink(tmp_path)

def run_cppcheck_on_c_files(root_dir, output_txt='./project/tests/cppcheck_report.txt'):
    exclude_dirs = ['01_getting-started', '02_lab-1', '03_lab-2', '04_lab-3','05_lab-project', '06_revision', 'mcc_generated_files']

    with open(output_txt, 'w') as report:
        for dirpath, dirnames, filenames in os.walk(root_dir):
            if any(excl in dirpath for excl in exclude_dirs):
                continue

            for fname in filenames:
                full_path = os.path.join(dirpath, fname)

                if fname.endswith(('.c', '.h')):
                    # Run cppcheck
                    result = subprocess.run(['cppcheck', '--enable=all', '--suppress=missingIncludeSystem', '--suppress=unusedFunction', full_path], capture_output=True, text=True)

                    if result.stdout:
                        report.write(f"Results for {full_path}:\n")
                        report.write(result.stdout)
                        report.write("\n" + "="*80 + "\n")
                    if result.stderr:
                        report.write(f"Error for {full_path}:\n")
                        report.write(result.stderr)
                        report.write("\n" + "="*80 + "\n")


if __name__ == '__main__':
    # run_cpplint_on_ino_files('C:\\Users\\Gonzalo Allendes\\OneDrive\\Escritorio\\Work & School\\Arizona State University\\capstone48_intro_to_microcontrollers\\deliverables')
    run_cppcheck_on_c_files('C:\\Users\\Gonzalo Allendes\\OneDrive\\Escritorio\\Work & School\\Arizona State University\\capstone48_intro_to_microcontrollers\\deliverables')


