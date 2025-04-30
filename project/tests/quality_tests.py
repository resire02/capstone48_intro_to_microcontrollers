import os
import subprocess
import tempfile
import shutil

def run_cpplint_on_ino_files(root_dir, output_txt='cpplint_report.txt'):
    with open(output_txt, 'w') as report:
        for dirpath, _, filenames in os.walk(root_dir):
            for fname in filenames:
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

if __name__ == '__main__':
    run_cpplint_on_ino_files('C:\\Users\\Gonzalo Allendes\\OneDrive\\Escritorio\\Work & School\\Arizona State University\\capstone48_intro_to_microcontrollers\\deliverables')


