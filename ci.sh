#/bin/bash
# 
# Local tests of CI jobs
# Run this from CI job docker container
set -ex

echo 'Running black'
black --check .

echo 'Running flake'
flake8 . 

echo 'Running pytest'
pytest

echo 'Finished tests'
