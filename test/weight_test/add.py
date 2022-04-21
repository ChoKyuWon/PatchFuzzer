import numpy as np

patched8 = []
patched = []

for i in range(1, 101):
	f_orig = open("./output/patched8/output{}/crashed_time".format(i), "r")
	patched8.append(int(f_orig.readline()))
	f_orig.close()

	f_pat = open("./output/patched8_only_target/output{}/crashed_time".format(i), "r")
	patched.append(int(f_pat.readline()))
	f_pat.close()

avg_orig = np.mean(patched8)
avg_pat = np.mean(patched)

std_orig = np.std(patched8)
std_pat = np.std(patched)

per_orig = np.percentile(patched8, [10, 90], interpolation='nearest')
per_pat = np.percentile(patched, [10, 90], interpolation='nearest')

f_orig = open("./patched8_result", "w")
f_pat = open("./patched8_only_target_result", "w")
for i in range(100):
	f_orig.write("{}\n".format(patched8[i]))
	f_pat.write("{}\n".format(patched[i]))

f_orig.write("\navg: {}\n".format(avg_orig))
f_pat.write("\navg: {}\n".format(avg_pat))

f_orig.write("std: {}\n".format(std_orig))
f_pat.write("std: {}\n".format(std_pat))

f_orig.write("10%: {}, 90%: {}\n".format(per_orig[0], per_orig[1]))
f_pat.write("10%: {}, 90%: {}\n".format(per_pat[0], per_pat[1]))

f_orig.close()
f_pat.close()

print("patched8")
print("avg: {}".format(avg_orig))
print("std: {}".format(std_orig))
print("10%: {}, 90%: {}".format(per_orig[0], per_orig[1]))

print("\npatched8_only_target")
print("avg: {}".format(avg_pat))
print("std: {}".format(std_pat))
print("10%: {}, 90%: {}".format(per_pat[0], per_pat[1]))

