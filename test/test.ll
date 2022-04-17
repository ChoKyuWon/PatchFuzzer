; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@__afl_area_ptr = external local_unnamed_addr global i8*
@__afl_prev_loc = external thread_local local_unnamed_addr global i32
@__my_trace_data = external local_unnamed_addr global i64
@str = private unnamed_addr constant [22 x i8] c"This is basic block 2\00", align 1

; Function Attrs: nofree nounwind uwtable
define dso_local i32 @main() local_unnamed_addr #0 !dbg !7 {
  tail call void @__my_trace() #4, !dbg !16
  %1 = load i32, i32* @__afl_prev_loc, align 4, !dbg !16, !nosanitize !2
  %2 = load i8*, i8** @__afl_area_ptr, align 8, !dbg !16, !nosanitize !2
  %3 = xor i32 %1, 29583, !dbg !16
  %4 = sext i32 %3 to i64, !dbg !16
  %5 = getelementptr i8, i8* %2, i64 %4, !dbg !16
  %6 = load i8, i8* %5, align 1, !dbg !16, !nosanitize !2
  %7 = add i8 %6, 1, !dbg !16
  store i8 %7, i8* %5, align 1, !dbg !16, !nosanitize !2
  store i32 14791, i32* @__afl_prev_loc, align 4, !dbg !16, !nosanitize !2
  call void @llvm.dbg.value(metadata i32 1, metadata !12, metadata !DIExpression()), !dbg !16
  tail call void @__my_trace() #4, !dbg !17
  %8 = load i32, i32* @__afl_prev_loc, align 4, !dbg !17, !nosanitize !2
  %9 = load i8*, i8** @__afl_area_ptr, align 8, !dbg !17, !nosanitize !2
  %10 = xor i32 %8, 53546, !dbg !17
  %11 = sext i32 %10 to i64, !dbg !17
  %12 = getelementptr i8, i8* %9, i64 %11, !dbg !17
  %13 = load i8, i8* %12, align 1, !dbg !17, !nosanitize !2
  %14 = add i8 %13, 1, !dbg !17
  store i8 %14, i8* %12, align 1, !dbg !17, !nosanitize !2
  store i32 26773, i32* @__afl_prev_loc, align 4, !dbg !17, !nosanitize !2
  call void @llvm.dbg.value(metadata i32 0, metadata !13, metadata !DIExpression()), !dbg !17
  %15 = tail call i32 @puts(i8* nonnull dereferenceable(1) getelementptr inbounds ([22 x i8], [22 x i8]* @str, i64 0, i64 0)), !dbg !18
  tail call void @__my_trace() #4, !dbg !16
  %16 = load i32, i32* @__afl_prev_loc, align 4, !dbg !16, !nosanitize !2
  %17 = load i8*, i8** @__afl_area_ptr, align 8, !dbg !16, !nosanitize !2
  %18 = xor i32 %16, 2382, !dbg !16
  %19 = sext i32 %18 to i64, !dbg !16
  %20 = getelementptr i8, i8* %17, i64 %19, !dbg !16
  %21 = load i8, i8* %20, align 1, !dbg !16, !nosanitize !2
  %22 = add i8 %21, 1, !dbg !16
  store i8 %22, i8* %20, align 1, !dbg !16, !nosanitize !2
  store i32 1191, i32* @__afl_prev_loc, align 4, !dbg !16, !nosanitize !2
  call void @llvm.dbg.value(metadata i32 10, metadata !12, metadata !DIExpression()), !dbg !16
  ret i32 0, !dbg !19
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

; Function Attrs: nofree noinline norecurse nounwind willreturn
define void @__my_trace() local_unnamed_addr #2 {
  %1 = load i64, i64* @__my_trace_data, align 8, !nosanitize !2
  %2 = add i64 %1, i8 1
  store i64 %2, i64* @__my_trace_data, align 8, !nosanitize !2
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @puts(i8* nocapture noundef readonly) local_unnamed_addr #3

attributes #0 = { nofree nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #2 = { nofree noinline norecurse nounwind willreturn }
attributes #3 = { nofree nounwind }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "Ubuntu clang version 12.0.0-3ubuntu1~20.04.5", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "test.c", directory: "/home/kyuwoncho18/sandbox/cfg-diff/test")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"Ubuntu clang version 12.0.0-3ubuntu1~20.04.5"}
!7 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 3, type: !8, scopeLine: 3, flags: DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !11)
!8 = !DISubroutineType(types: !9)
!9 = !{!10}
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !{!12, !13}
!12 = !DILocalVariable(name: "a", scope: !7, file: !1, line: 4, type: !10)
!13 = !DILocalVariable(name: "b1", scope: !14, file: !1, line: 6, type: !10)
!14 = distinct !DILexicalBlock(scope: !15, file: !1, line: 5, column: 11)
!15 = distinct !DILexicalBlock(scope: !7, file: !1, line: 5, column: 8)
!16 = !DILocation(line: 0, scope: !7)
!17 = !DILocation(line: 0, scope: !14)
!18 = !DILocation(line: 7, column: 9, scope: !14)
!19 = !DILocation(line: 13, column: 1, scope: !7)
