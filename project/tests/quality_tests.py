import os
import subprocess
import tempfile
import shutil
import re
import pandas as pd

def run_cpplint_on_ino_files(root_dir, output_path='./cpplint_raw.txt'):
    exclude_dirs = []

    with open(output_path, 'w') as report:
        for dirpath, _, filenames in os.walk(root_dir):
            for fname in filenames:
                if fname.startswith('Base_Example'):
                    continue
                if fname.endswith(('.ino')):
                    full_path = os.path.join(dirpath, fname)
                    clean_path = os.path.normpath(full_path).replace(os.sep, '/')

                    # Create a temp .cpp copy
                    with tempfile.NamedTemporaryFile(suffix='.cpp', delete=False) as tmp:
                        tmp_path = tmp.name
                        shutil.copyfile(clean_path, tmp_path)

                    # Run cpplint
                    result = subprocess.run(['cpplint', tmp_path], capture_output=True, text=True)
                    result = re.sub(re.escape(tmp_path), clean_path, result.stderr)

                    # Delete temp file
                    os.unlink(tmp_path)

                    # Replace temp path with original path in the report
                    report.write(f"Linting {clean_path} (as .cpp)\n")
                    report.write(result)
                    report.write("\n" + "="*80 + "\n")


def run_cppcheck_on_c_files(root_dir, output_txt='./cppcheck_raw.txt'):
    exclude_dirs = ['01_getting-started', '02_lab-1', '03_lab-2', '04_lab-3','05_lab-project', '06_revision', 'mcc_generated_files']

    with open(output_txt, 'w') as report:
        report.write("\n" + "=" * 80 + "\n")
        for dirpath, dirnames, filenames in os.walk(root_dir):
            if any(excl in dirpath for excl in exclude_dirs):
                continue

            for fname in filenames:
                full_path = os.path.join(dirpath, fname)

                if fname.endswith(('.c', '.h')):
                    # Run cppcheck
                    result = subprocess.run(['cppcheck', '--enable=all', '--suppress=missingIncludeSystem', '--suppress=unusedFunction', full_path], capture_output=True, text=True)
                    folder = os.path.basename(dirpath).replace('\\', '/')
                    if result.stdout:
                        report.write(f"Analyzing file: {folder}\\{fname}:\n\n")
                        report.write(result.stdout.replace('\\', '/'))
                    if result.stderr:
                        report.write(f"\nResults for {folder}\\{fname}:\n\n")
                        report.write(result.stderr.replace('\\', '/'))
                        report.write("\n" + "=" * 80 + "\n")

def tabulate_results(input_txt: str, output_txt: str) -> None:
    # Load file
    with open(input_txt, 'r', encoding='utf-8') as f:
        content = f.read()

    if ('cpplint' in input_txt):
        # Regex to match typical cpplint output lines
        pattern = re.compile(
            r'(?P<file>.+?):(?P<line>\d+):\s+(?P<message>.+?)\s+\[(?P<check>[^\]]+)\]\s+\[(?P<severity>\d+)\]'
        )

        # Find all matches
        matches = pattern.findall(content)

        # Convert to DataFrame
        df = pd.DataFrame(matches, columns=['File', 'Line', 'Message', 'Check', 'Severity'])

        # Optional: sort by file and line number
        df['Line'] = df['Line'].astype(int)
        df = df.sort_values(by=['File', 'Line'])

    elif ('cppcheck' in input_txt):
        # Regex to match typical cppcheck output lines
        pattern = re.compile(
            r'(?P<file>.+?):(?P<line>\d+):(?P<col>\d+):\s(?P<severity>\w+):\s(?P<message>.+?)\s\[(?P<check>[^\]]+)\]')

        # Find all matches
        matches = pattern.findall(content)

        # Filter nofiles
        filtered_matches = [m for m in matches if 'nofile' not in m[0]]

        # Convert to DataFrame
        df = pd.DataFrame(filtered_matches, columns=['File', 'Line', 'Column', 'Severity', 'Message', 'Check'])

        # Optional: sort by file and line number
        df['Line'] = df['Line'].astype(int)
        df = df.sort_values(by=['File', 'Line'])

    # Output as Markdown (you could also save to CSV or HTML)
    with open(output_txt, 'w', encoding='utf-8') as f:
        f.write(df.to_markdown(index=False))

if __name__ == '__main__':
    os.chdir(os.path.dirname(__file__))  # sets working directory to script location
    print(os.getcwd())
    run_cpplint_on_ino_files('./../../deliverables')
    run_cppcheck_on_c_files('./../../deliverables')
    tabulate_results('cpplint_raw.txt', 'cpplint_report.txt')
    tabulate_results('cppcheck_raw.txt', 'cppcheck_report.txt')


